/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

module;

#include <AK/Platform.h>

export module AK:IterationDecision;

namespace AK {

export enum class IterationDecision {
    Continue,
    Break,
};

}

#if USING_AK_GLOBALLY
export using AK::IterationDecision;
#endif
