#include "openai.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <format>

nlohmann::json build_request(std::string model, std::string prompt, uint32_t n_tokens, float temperature) {
  nlohmann::json j;
  j["model"] = model;
  j["prompt"] = prompt;
  j["max_tokens"] = n_tokens;
  j["temperature"] = temperature;
  return j;
}

std::string build_qwen_prompt(std::string instructions, std::string query) {
  return std::format(
    "<|im_start|>system\n{}<|im_end|>\n<|im_start|>user\n{}<|im_end|>\n<|im_start|>assistant", instructions, query
  );
}

int main() {
  openai::start("nokey", "", true, "http://localhost:8033/v1/");

  // this doesnt matter with llama.cpp
  auto model = "qwen_qwen3-vl-8b-instruct-gguf_qwen3vl-8b-instruct-q4_k_m.gguf";
  auto instruction = "You are a coding agent that only replies with compilable code. Do not include any markdown, formatting, descriptions or explanatory text.";
  auto query = "Write me the sieve of eratosthenes in C.";

  auto req = build_request(model, build_qwen_prompt(instruction, query), 1024, 0.1);
  auto completion = openai::completion().create(req);
  
  std::cout << completion["choices"][0]["text"].get<std::string>() << '\n'; 
}
