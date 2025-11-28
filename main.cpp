#include "openai.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <format>

struct CompletionBody {
  std::string model;
  std::string prompt;
  int max_tokens;
  float temperature;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(CompletionBody, model, prompt, max_tokens, temperature)
};


int main() {
  openai::start("nokey", "", true, "http://localhost:8033/v1/");

  auto model = "/home/henry/.cache/llama.cpp/qwen_qwen3-vl-8b-instruct-gguf_qwen3vl-8b-instruct-q4_k_m.gguf";
  auto instruction = "You are a coding agent that only replies with compilable code. Do not include any markdown, formatting, descriptions or explanatory text.";
  auto query = "Write me a zig program that adds two numbers.";

  CompletionBody cb {
    model,
    std::format("<|im_start|>system\n{}\n<|im_start|>user\n{}<|im_start|>assistant", instruction, query),
    100,
    0.1
  };

  nlohmann::json j = cb;

  auto completion = openai::completion().create(cb);
  
  std::cout << completion["choices"][0]["text"].get<std::string>() << '\n'; 
}
