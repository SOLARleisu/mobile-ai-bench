// Copyright 2018 Xiaomi, Inc.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef AIBENCH_BENCHMARK_BENCHMARK_H_
#define AIBENCH_BENCHMARK_BENCHMARK_H_

#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "aibench/executors/base_executor.h"

#define BENCHMARK_CONCAT(a, b, c) a##b##c
#define AIBENCH_BENCHMARK(executor, model_name, framework, runtime, \
                          model_file, input_names, input_files, input_shapes, \
                          output_names, output_shapes) \
  static ::aibench::benchmark::Benchmark \
      *BENCHMARK_CONCAT(model_name, framework, runtime) = \
    (new ::aibench::benchmark::Benchmark(executor, #model_name, #model_file, \
         input_names, input_files, input_shapes, output_names, output_shapes))

namespace aibench {
namespace benchmark {

class Benchmark {
 public:
  Benchmark(BaseExecutor *executor,
            const char *model_name,
            const char *model_file,
            std::vector<std::string> input_names,
            std::vector<std::string> input_files,
            std::vector<std::vector<int64_t>> input_shapes,
            std::vector<std::string> output_names,
            std::vector<std::vector<int64_t>> output_shapes);

  static Status Run(const char *model_name, const char *framework,
                    const char *runtime, int run_interval, int num_threads);

 private:
  BaseExecutor *executor_;
  std::string model_name_;
  std::string model_file_;
  std::vector<std::string> input_names_;
  std::vector<std::string> input_files_;
  std::vector<std::vector<int64_t>> input_shapes_;
  std::vector<std::string> output_names_;
  std::vector<std::vector<int64_t>> output_shapes_;

  void Register();
  Status Run(double *init_seconds, double *run_seconds, int num_threads);
};

int64_t NowMicros();

}  // namespace benchmark
}  // namespace aibench

#endif  // AIBENCH_BENCHMARK_BENCHMARK_H_
