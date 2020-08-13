/*
 * Copyright (C) 2020 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "mock_logger.h"

namespace mp = multipass;
namespace mpl = multipass::logging;
namespace mpt = multipass::test;
using namespace testing;

mpt::MockLogger::MockLogger(const PrivatePass&)
{
}

auto mpt::MockLogger::inject() -> Scope
{
    return Scope{};
}

mpt::MockLogger::Scope::Scope()
{
    mpl::set_logger(mock_logger);
}

mpt::MockLogger::Scope::~Scope()
{
    mpl::set_logger(nullptr);
}

void mpt::MockLogger::expect_log(mpl::Level lvl, const std::string& substr)
{
    EXPECT_CALL(*this, log(lvl, _, make_cstring_matcher(HasSubstr(substr))));
}

void mpt::MockLogger::screen_logs(mpl::Level lvl)
{
    for (auto i = 0; i <= mpl::enum_type(mpl::Level::trace); ++i)
    {
        auto times = i < mpl::enum_type(lvl) ? Exactly(0) : AnyNumber();
        EXPECT_CALL(*this, log(mpl::level_from(i), _, _)).Times(times);
    }
}
