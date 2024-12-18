#include <torch/torch.h>
#include <iostream>

int main(int argc, char *argv[])
{
	// 初始化数据 X 和 y
	torch::Tensor X = torch::tensor({{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}}, torch::kFloat32);
	torch::Tensor y = torch::tensor({0.0, 1.0, 2.0}, torch::kFloat32);

	// 初始化权重和偏差
	torch::Tensor w = torch::rand({2}, torch::requires_grad(true).dtype(torch::kFloat32));
	torch::Tensor b = torch::randn({1}, torch::requires_grad(true));

	// 设置学习率和迭代次数
	double learning_rate = 0.01;
	int num_iterations = 10000;

	for (int i = 0; i < num_iterations; ++i) {
		// 预测并计算损失
		torch::Tensor prediction = torch::mm(X, w.view({2, 1})) + b;
		torch::Tensor loss = torch::mse_loss(prediction.view_as(y), y);

		// 反向传播来计算梯度
		loss.backward();

		// 更新参数
		{
			torch::NoGradGuard no_grad;  // 更新时不计算梯度
			w -= learning_rate * w.grad();
			b -= learning_rate * b.grad();

			// 清除梯度
			w.grad().zero_();
			b.grad().zero_();
		}

		// 每隔100轮输出一次损失
		if (i % 100 == 0) {
			std::cout << "Iteration " << i << " Loss: " << loss.item<float>() << std::endl;
		}
	}

	// 打印最终学到的权重和偏差
	std::cout << "Weight:\n" << w << std::endl;
	std::cout << "Bias:\n" << b << std::endl;

	return 0;
}
