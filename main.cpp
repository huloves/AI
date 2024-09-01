#include <torch/script.h>
#include <torch/torch.h>

#include <iostream>
#include <memory>

void dynamic_calculation_graph1(void)
{
        torch::Tensor x = torch::ones({2, 2}, torch::requires_grad(true));
	torch::Tensor y = x + 2;
        torch::Tensor z = y * y;
        torch::Tensor t = torch::mean(z);

	std::cout << "x:\n" << x << std::endl;
	std::cout << "y:\n" << y << std::endl;
	std::cout << "z:\n" << z << std::endl;
        std::cout << "t:\n" << t << std::endl;

	std::cout << y.grad_fn()->name() << std::endl;
        std::cout << z.grad_fn()->name() << std::endl;
        std::cout << t.grad_fn()->name() << std::endl;

        t.backward();
        std::cout << "t.grad():\n" << t.grad() << std::endl;
        std::cout << "z.grad():\n" << z.grad() << std::endl;
        std::cout << "y.grad():\n" << y.grad() << std::endl;
        std::cout << "x.grad():\n" << x.grad() << std::endl;
}

void dynamic_calculation_graph2(void)
{
        torch::Tensor s = torch::tensor({{0.01, 0.02}}, torch::requires_grad(true));
        torch::Tensor x = torch::ones({2, 2}, torch::requires_grad(true));

	std::cout << "s:\n" << s << std::endl;
        std::cout << "x:\n" << x << std::endl;

        for (int i = 0; i < 10; i++)
                s = s.mm(x);
        
        auto z = torch::mean(s);

        z.backward();

        std::cout << "x.grad():\n" << x.grad() << std::endl;
}

void predict_room(void)
{
        torch::Tensor x = torch::linspace(0, 100, 100, torch::dtype(torch::kFloat));
        torch::Tensor rand = torch::randn(100) * 10;
        torch::Tensor y = x + rand;
        torch::Tensor x_train = x.index({torch::indexing::Slice(0, -10)});
        torch::Tensor x_test = x.index({torch::indexing::Slice(-10, x.numel())});

        std::cout << "x:\n" << x << std::endl;
        std::cout << "x_train:\n" << x_train << std::endl;
        std::cout << "x_test:\n" << x_test << std::endl;
}

void learn_torch(void)
{
	if (torch::cuda::is_available()) {
		std::cout << "support CUDA" << std::endl;
	} else {
		std::cout << "not support CUDA" << std::endl;
	}

        predict_room();
}

bool learn = true;

int main(int argc, const char* argv[])
{
        if (learn == true) {
	        learn_torch();
        } else {
                if(argc != 2) {
                    std::cerr << "usage: main <path-to-exported-script-module>\n";
                    return -1;
                }

                torch::Device device(torch::kCUDA);
                // Deserialize the ScriptModule from a file using torch::jit::load()
                torch::jit::script::Module module = torch::jit::load(argv[1]);
                module.to(device);

                // Create a vector of inputs
                std::vector<torch::jit::IValue> inputs;
                inputs.push_back(torch::ones({1, 3, 224, 224}).to(device));

                // Exectute the model
                at::Tensor output = module.forward(inputs).toTensor();

                std::cout << output.slice(/*dims=*/1, /*start=*/0, /*end=*/5) << '\n';

                std::cout << "ok\n";
        }
}
