/**
 * Copyright (C) 2013 - present by OpenGamma Inc. and the OpenGamma group of companies
 *
 * Please see distribution for license.
 */

#include <iostream>
#include "numeric.hh"
#include "expression.hh"
#include "terminal.hh"

using namespace std;

namespace librdag
{

/*
 * Non-autogenerated OGNumeric methods
 */

OGNumeric::~OGNumeric()
{
}

const COPY*
OGNumeric::asCOPY() const
{
  return nullptr;
}

const SELECTRESULT*
OGNumeric::asSELECTRESULT() const
{
  return nullptr;
}

const NORM2*
OGNumeric::asNORM2() const
{
  return nullptr;
}

const PINV*
OGNumeric::asPINV() const
{
  return nullptr;
}

const TRANSPOSE*
OGNumeric::asTRANSPOSE() const
{
  return nullptr;
}

const CTRANSPOSE*
OGNumeric::asCTRANSPOSE() const
{
  return nullptr;
}

const SVD*
OGNumeric::asSVD() const
{
  return nullptr;
}

const MTIMES*
OGNumeric::asMTIMES() const
{
  return nullptr;
}

const LU*
OGNumeric::asLU() const
{
  return nullptr;
}

const OGExpr*
OGNumeric::asOGExpr() const
{
  return nullptr;
}

const OGTerminal*
OGNumeric::asOGTerminal() const
{
  return nullptr;
}

const OGRealScalar*
OGNumeric::asOGRealScalar() const
{
  return nullptr;
}

const OGComplexScalar*
OGNumeric::asOGComplexScalar() const
{
  return nullptr;
}

const OGIntegerScalar*
OGNumeric::asOGIntegerScalar() const
{
  return nullptr;
}

const OGRealMatrix*
OGNumeric::asOGRealMatrix() const
{
  return nullptr;
}

const OGComplexMatrix*
OGNumeric::asOGComplexMatrix() const
{
  return nullptr;
}

const OGLogicalMatrix*
OGNumeric::asOGLogicalMatrix() const
{
  return nullptr;
}

const OGRealDiagonalMatrix*
OGNumeric::asOGRealDiagonalMatrix() const
{
  return nullptr;
}

const OGComplexDiagonalMatrix*
OGNumeric::asOGComplexDiagonalMatrix() const
{
  return nullptr;
}

const OGRealSparseMatrix*
OGNumeric::asOGRealSparseMatrix() const
{
  return nullptr;
}

const OGComplexSparseMatrix*
OGNumeric::asOGComplexSparseMatrix() const
{
  return nullptr;
}

ExprType_t OGNumeric::getType() const
{
  return UNKNOWN_EXPR_ENUM;
}


} // namespace librdag
