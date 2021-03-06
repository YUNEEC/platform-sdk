// AirMap Platform SDK
// Copyright © 2018 AirMap, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <airmap/qt/rulesets.h>

std::shared_ptr<airmap::qt::RuleSets> airmap::qt::RuleSets::create(const std::shared_ptr<Dispatcher>& dispatcher,
                                                                   const std::shared_ptr<airmap::Client>& client) {
  return std::shared_ptr<RuleSets>{new RuleSets{dispatcher, client}};
}

airmap::qt::RuleSets::RuleSets(const std::shared_ptr<Dispatcher>& dispatcher,
                               const std::shared_ptr<airmap::Client>& client)
    : dispatcher_{dispatcher}, client_{client} {
}

void airmap::qt::RuleSets::search(const Search::Parameters& parameters, const Search::Callback& cb) {
  dispatcher_->dispatch_to_native([this, sp = shared_from_this(), parameters, cb]() {
    sp->client_->rulesets().search(parameters, [this, sp, cb](const auto& result) {
      sp->dispatcher_->dispatch_to_qt([sp, result, cb]() { cb(result); });
    });
  });
}

void airmap::qt::RuleSets::for_id(const ForId::Parameters& parameters, const ForId::Callback& cb) {
  dispatcher_->dispatch_to_native([this, sp = shared_from_this(), parameters, cb]() {
    sp->client_->rulesets().for_id(parameters, [this, sp, cb](const auto& result) {
      sp->dispatcher_->dispatch_to_qt([sp, result, cb]() { cb(result); });
    });
  });
}

void airmap::qt::RuleSets::fetch_rules(const FetchRules::Parameters& parameters, const FetchRules::Callback& cb) {
  dispatcher_->dispatch_to_native([this, sp = shared_from_this(), parameters, cb]() {
    sp->client_->rulesets().fetch_rules(parameters, [this, sp, cb](const auto& result) {
      sp->dispatcher_->dispatch_to_qt([sp, result, cb]() { cb(result); });
    });
  });
}

void airmap::qt::RuleSets::evaluate_rulesets(const EvaluateRules::Parameters& parameters,
                                             const EvaluateRules::Callback& cb) {
  dispatcher_->dispatch_to_native([this, sp = shared_from_this(), parameters, cb]() {
    sp->client_->rulesets().evaluate_rulesets(parameters, [this, sp, cb](const auto& result) {
      sp->dispatcher_->dispatch_to_qt([sp, result, cb]() { cb(result); });
    });
  });
}

void airmap::qt::RuleSets::evaluate_flight_plan(const EvaluateFlightPlan::Parameters& parameters,
                                                const EvaluateFlightPlan::Callback& cb) {
  dispatcher_->dispatch_to_native([this, sp = shared_from_this(), parameters, cb]() {
    sp->client_->rulesets().evaluate_flight_plan(parameters, [this, sp, cb](const auto& result) {
      sp->dispatcher_->dispatch_to_qt([sp, result, cb]() { cb(result); });
    });
  });
}
