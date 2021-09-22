// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <gtest/gtest.h>

#include <ie_core.hpp>
#include <ie_ngraph_utils.hpp>
#include <ngraph/ngraph.hpp>
#include <shared_test_classes/base/layer_test_utils.hpp>
#include <tuple>

#include "logical.hpp"

using namespace ngraph;
using namespace InferenceEngine;
using LogicalTypes = ngraph::helpers::LogicalTypes;

namespace reference_tests {
namespace LogicalOpsRefTestDefinitions {
namespace {

std::vector<RefLogicalParams> generateLogicalParams() {
    std::vector<RefLogicalParams> logicalParams {
        Builder {}
            .opType(LogicalTypes::LOGICAL_OR)
            .inputs({{{2, 2}, element::boolean, std::vector<char> {true, false, true, false}},
                     {{2, 2}, element::boolean, std::vector<char> {false, true, true, false}}})
            .expected({{2, 2}, element::boolean, std::vector<char> {true, true, true, false}}),
        Builder {}
            .opType(LogicalTypes::LOGICAL_OR)
            .inputs({{{2, 1, 2, 1}, element::boolean, std::vector<char> {true, false, true, false}},
                     {{1, 1, 2, 1}, element::boolean, std::vector<char> {true, false}}})
            .expected({{2, 1, 2, 1}, element::boolean, std::vector<char> {true, false, true, false}}),
        Builder {}
            .opType(LogicalTypes::LOGICAL_OR)
            .inputs({{{3, 4}, element::boolean, std::vector<char> {true, true, true, true, true, false, true, false, false, true, true, true}},
                     {{3, 4}, element::boolean, std::vector<char> {true, true, true, true, true, true, true, false, false, true, true, false}}})
            .expected({{3, 4}, element::boolean, std::vector<char> {true, true, true, true, true, true, true, false, false, true, true, true}})};
    return logicalParams;
}

INSTANTIATE_TEST_SUITE_P(smoke_LogicalOr_With_Hardcoded_Refs, ReferenceLogicalLayerTest, ::testing::ValuesIn(generateLogicalParams()),
                         ReferenceLogicalLayerTest::getTestCaseName);

}  // namespace
}  // namespace LogicalOpsRefTestDefinitions
}  // namespace reference_tests