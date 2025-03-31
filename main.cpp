#include<iostream>
#include<Eigen/Eigen>

using namespace std;
using namespace Eigen;


int main()
{
      // Initialize the vector with the exact solution
      Vector2d ex_sol;
      ex_sol << -1, -1;
      double ex_sol_norm = ex_sol.norm();

      // Initialize the given matrices and vectors
      // First system
      Matrix2d A1;
      A1 << 5.547001962252291e-01, -3.770900990025203e-02,
            8.320502943378437e-01, -9.992887623566787e-01;
      
      Vector2d b1;
      b1 << -5.169911863249772e-01, 1.672384680188350e-01;

      // Second system
      Matrix2d A2;
      A2 << 5.547001962252291e-01, -5.540607316466765e-01,
            8.320502943378437e-01, -8.324762492991313e-01;

      Vector2d b2;
      b2 << -6.394645785530173e-04, 4.259549612877223e-04;

      // Third system
      Matrix2d A3;
      A3 << 5.547001962252291e-01, -5.547001955851905e-01,
            8.320502943378437e-01, -8.320502947645361e-01;

      Vector2d b3;
      b3 << -6.400391328043042e-10, 4.266924591433963e-10;

      // Create an array with the matrices and one with the vectors
      array<Matrix2d,3> matrices = {A1, A2, A3};
      array<Vector2d,3> vectors = {b1, b2, b3};

      for(int i = 0; i < 3; i++)
      {
            const Matrix2d& A = matrices[i];
            const Vector2d& b = vectors[i];
            
            // PA=LU factorization
            // Factorize the matrix and solve the system Ax = b
            Vector2d x_lu = A.lu().solve(b);

            // Compute relative error
            double rel_err_lu = (ex_sol - x_lu).norm() / ex_sol_norm;
            

            // QR factorization
            //Factorize the matrix and solve the system Ax = b
            Vector2d x_qr = A.colPivHouseholderQr().solve(b);

            // Compute relative error
            double rel_err_qr = (ex_sol - x_qr).norm() / ex_sol_norm;

            // Print results
            cout << "The relative error of system " << i+1 << " using PA=LU is: " << rel_err_lu
                 << " and using QR is: " << rel_err_qr << endl;
      }

      return 0;
}
