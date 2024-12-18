#include <mlpack/core.hpp>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include <armadillo>
#include <iostream>

int main(int argc, char *argv[])
{
	// 使用Armadillo库定义训练数据集
	// 每列为一个样本，符合MLPACK的数据布局要求
	arma::mat X = arma::mat("0 0; 1 1; 2 2").t();
	arma::rowvec y = {0, 1, 2}; // 响应变量，也按照列向量组织

	// 创建线性回归对象
	mlpack::regression::LinearRegression model;

	// 训练模型
	model.Train(X, y);

	// 获取模型的系数
	arma::vec coefficients = model.Parameters();

	// 输出系数（第一个元素是截距，其余为系数）
	std::cout << "Intercept: " << coefficients[0] << std::endl;
	std::cout << "Coefficients: ";
	for(size_t i = 1; i < coefficients.n_elem; ++i) {
		std::cout << coefficients[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
