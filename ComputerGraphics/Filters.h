#pragma once

#define _FILTER_NULLPTR std::ranges::views::filter([](auto* pointer){return pointer;})
