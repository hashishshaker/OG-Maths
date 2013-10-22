/**
 * Copyright (C) 2013 - present by OpenGamma Inc. and the OpenGamma group of companies
 *
 * Please see distribution for license.
 */

#include "gtest/gtest.h"
#include "entrypt.hh"
#include "expression.hh"
#include "terminal.hh"
#include "test/terminals.hh"

using namespace std;
using namespace librdag;

class EntryptOneNodeTest: public ::testing::TestWithParam<const OGTerminal*> {};

TEST_P(EntryptOneNodeTest, TerminalTypes)
{
  // Test "base case" - one node
  const OGNumeric* node = GetParam();
  // Check that result is not null
  const OGNumeric* result = entrypt(node);
  ASSERT_NE(nullptr, result);
  delete result;
  delete node;
}

INSTANTIATE_TEST_CASE_P(ValueParam, EntryptOneNodeTest, ::testing::ValuesIn(terminals));

/**
 * A TreeResultPair consists of a tree and the terminal it is expected to evaluate to.
 */
typedef pair<const OGNumeric*, const OGNumeric*> TreeResultPair;

/**
 * run_entrypt calls entrypt, checks the result and cleans up. This is common to
 * all entrypt tests. Factoring it into a function that is called from TEST functions
 * allows the tests to keep separate names for clarity.
 */
void run_entrypt(TreeResultPair param)
{
  const OGNumeric* node = param.first;
  const OGTerminal* expectedResult = param.second->asOGTerminal();
  const OGTerminal *result = entrypt(node)->asOGTerminal();
  ASSERT_NE(result, nullptr);
  EXPECT_TRUE((*result)==(*expectedResult));
  delete node;
  delete expectedResult;
  // FIXME Ad-hoc manual cleanup of result data. This needs to be handled
  // sensibly by a Register in the future.
  const OGRealMatrix* realMatrix = result->asOGRealMatrix();
  if (realMatrix != nullptr)
  {
    delete[] realMatrix->getData();
  }
  const OGComplexMatrix* complexMatrix = result->asOGComplexMatrix();
  if (complexMatrix != nullptr)
  {
    delete[] complexMatrix->getData();
  }
  delete result;

}

/**
 * Entrypt with NEGATE nodes
 */
class EntryptNegateTest: public ::testing::TestWithParam<TreeResultPair> {};

TEST_P(EntryptNegateTest, Running)
{
  run_entrypt(GetParam());
}

TreeResultPair negatepair(double v)
{
  ArgContainer* args = new ArgContainer();
  args->push_back(new OGRealScalar(v));
  const OGNumeric* negate = new NEGATE(args);
  const OGNumeric* expected = new OGRealScalar(-v);
  return TreeResultPair(negate, expected);
}

TreeResultPair doublenegate(double v)
{
  ArgContainer* args = new ArgContainer();
  args->push_back(new OGRealScalar(v));
  const OGNumeric* negate = new NEGATE(args);
  args = new ArgContainer();
  args->push_back(negate);
  negate = new NEGATE(args);
  const OGNumeric* expected = new OGRealScalar(v);
  return TreeResultPair(negate, expected);
}

double realData[6] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
double realNegData[6] = { -1.0, -2.0, -3.0, -4.0, -5.0, -6.0 };

TreeResultPair negaterealmatrix()
{
  const OGTerminal* ogrealmatrix = new OGRealMatrix(realData, 2, 3);
  ArgContainer* arg = new ArgContainer();
  arg->push_back(ogrealmatrix);
  const OGNumeric* negate = new NEGATE(arg);
  const OGTerminal* ogrealnegmatrix = new OGRealMatrix(realNegData, 2, 3);
  return TreeResultPair(negate, ogrealnegmatrix);
}

complex16 complexData[6] = { {1.0, 2.0}, {3.0, 4.0},  {5.0,  6.0},
                             {7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0} };
complex16 complexNegData[6] = { {-1.0, -2.0}, {-3.0, -4.0},  {-5.0,  -6.0},
                                {-7.0, -8.0}, {-9.0, -10.0}, {-11.0, -12.0} };

TreeResultPair negatecomplexmatrix()
{
  const OGTerminal* ogcomplexmatrix = new OGComplexMatrix(complexData, 2, 3);
  ArgContainer* arg = new ArgContainer();
  arg->push_back(ogcomplexmatrix);
  const OGNumeric* negate = new NEGATE(arg);
  const OGTerminal* ogcomplexnegmatrix = new OGComplexMatrix(complexNegData, 2, 3);
  return TreeResultPair(negate, ogcomplexnegmatrix);
}

TreeResultPair negates[] =
   { negatepair(1.0), negatepair(-1.0), negatepair(0.0),
     doublenegate(1.0), doublenegate(-1.0), doublenegate(0.0),
     negaterealmatrix(), negatecomplexmatrix() };

INSTANTIATE_TEST_CASE_P(ValueParam, EntryptNegateTest, ::testing::ValuesIn(negates));

/**
 * Entrypt with PLUS nodes
 */
class EntryptPlusTest: public ::testing::TestWithParam<TreeResultPair> {} ;

TEST_P(EntryptPlusTest, Running)
{
  run_entrypt(GetParam());
}

TreeResultPair plustestsimple()
{
  ArgContainer* args = new ArgContainer();
  args->push_back(new OGRealScalar(2.0));
  args->push_back(new OGRealScalar(3.0));
  const OGNumeric* plus = new PLUS(args);
  const OGNumeric* expected = new OGRealScalar(2.0+3.0);
  return TreeResultPair(plus, expected);
}

TreeResultPair plustesttwoplus()
{
  ArgContainer* args = new ArgContainer();
  args->push_back(new OGRealScalar(2.0));
  args->push_back(new OGRealScalar(3.0));
  const OGNumeric* plus = new PLUS(args);
  args = new ArgContainer();
  args->push_back(new OGRealScalar(1.0));
  args->push_back(plus);
  plus = new PLUS(args);
  const OGNumeric* expected = new OGRealScalar(1.0+2.0+3.0);
  return TreeResultPair(plus, expected);
}

TreeResultPair plustestbigtree()
{
  const OGNumeric* bigtree = new OGRealScalar(0.0);
  double sum = 0.0;
  for (int i = 0; i < 5000; ++i)
  {
    sum += i;
    ArgContainer* args = new ArgContainer();

    if (i%2 == 0)
    {
      args->push_back(new OGRealScalar(i));
      args->push_back(bigtree);
    }
    else
    {
      args->push_back(bigtree);
      args->push_back(new OGRealScalar(i));
    }
    bigtree = new PLUS(args);
  }

  return TreeResultPair(bigtree, new OGRealScalar(sum));
}

TreeResultPair pluses[] = { plustestsimple(), plustesttwoplus(), plustestbigtree() };

INSTANTIATE_TEST_CASE_P(ValueParam, EntryptPlusTest, ::testing::ValuesIn(pluses));

