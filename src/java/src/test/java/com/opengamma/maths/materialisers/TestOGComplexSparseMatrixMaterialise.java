/**
 * Copyright (C) 2013 - present by OpenGamma Inc. and the OpenGamma group of companies
 *
 * Please see distribution for license.
 */

package com.opengamma.maths.materialisers;

import java.util.Arrays;

import org.testng.annotations.DataProvider;
import org.testng.annotations.Test;

import com.opengamma.maths.datacontainers.matrix.OGComplexSparseMatrix;
import com.opengamma.maths.exceptions.MathsException;
import com.opengamma.maths.materialisers.Materialisers;

public class TestOGComplexSparseMatrixMaterialise {

  @DataProvider
  public Object[][] dataContainer() {
    Object[][] obj = new Object[3][6];

    obj[0][0] = new int[] {0, 1};
    obj[0][1] = new int[] {0};
    obj[0][2] = new double[] {5.0};
    obj[0][3] = new double[] {50.0};
    obj[0][4] = 1;
    obj[0][5] = 1;

    obj[1][0] = new int[] {0, 2, 2};
    obj[1][1] = new int[] {0, 1};
    obj[1][2] = new double[] {1.0, 2.0};
    obj[1][3] = new double[] {10.0, 20.0};
    obj[1][4] = 2;
    obj[1][5] = 2;

    obj[2][0] = new int[] {0, 3, 6, 10, 12, 12};
    obj[2][1] = new int[] {0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 2, 3};
    obj[2][2] = new double[] { 1.0, 5.0,  0.0,  2.0,  0.0,  10.0,  0.0,  7.0, 11.0, 15.0,   0.0,   0.0};
    obj[2][3] = new double[] {10.0, 0.0, 90.0, 20.0, 60.0, 100.0, 30.0, 70.0,  0.0,  0.0, 120.0, 160.0};
    obj[2][4] = 4;
    obj[2][5] = 5;

    return obj;
  };

  @Test(dataProvider = "dataContainer")
  public void materialiseToOGTerminal(int[] colPtr, int[] rowIdx, double[] realpart, double[] imagpart, int rows, int cols) {
    OGComplexSparseMatrix tmp = new OGComplexSparseMatrix(colPtr, rowIdx, realpart, imagpart, rows, cols);
    OGComplexSparseMatrix answer = (OGComplexSparseMatrix) Materialisers.toOGTerminal(tmp);
    if (!Arrays.equals(tmp.getData(), answer.getData())) {
      throw new MathsException("Arrays are not equal");
    }
    if (tmp.getRows() != answer.getRows()) {
      throw new MathsException("Rows are not equal");
    }
    if (tmp.getCols() != answer.getCols()) {
      throw new MathsException("Cols are not equal");
    }
  }

}
