//
// Created by treys on 6/7/2022.
//

#ifndef SAMPLE_LOCALES_HPP
#define SAMPLE_LOCALES_HPP

#include <string_view>

#include "usf/develop/usf_locales_territories.hpp"
#include "usf/develop/usf_locale.hpp"

using namespace std::literals::string_view_literals;

inline constexpr usf::Locale en_US {
    .identity = {
        .revision = 41,
        .language = usf::Languages::en,
        .territory = usf::Territories::US
    },
    .numbers = {
        .symbols = {
            .decimal = u8"."sv,
            .group = u8","sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8":"sv
        }
    }
};

inline constexpr usf::Locale es_ES {
    .identity = {
        .revision = 41,
        .language = usf::Languages::es,
        .territory = usf::Territories::ES
    },
    .numbers = {
        .symbols = {
            .decimal = u8","sv,
            .group = u8"."sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8":"sv
        }
    }
};

inline constexpr usf::Locale da_DK {
    .identity = {
        .revision = 41,
        .language = usf::Languages::da,
        .territory = usf::Territories::DK
    },
    .numbers = {
        .symbols = {
            .decimal = u8","sv,
            .group = u8"."sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8"."sv
        }
    }
};

inline constexpr usf::Locale ja_JP {
    .identity = {
        .revision = 41,
        .language = usf::Languages::ja,
        .territory = usf::Territories::JP
    },
    .numbers = {
        .symbols = {
            .decimal = u8"."sv,
            .group = u8","sv,
            .list = u8";"sv,
            .percent_sign = u8"%"sv,
            .plus_sign = u8"+"sv,
            .minus_sign = u8"-"sv,
            .exponential = u8"E"sv,
            .superscripting_exponent = u8"×"sv,
            .per_mille = u8"‰"sv,
            .infinity = u8"∞"sv,
            .nan = u8"NaN"sv,
            .time_separator = u8":"sv
        }
    }
};

#endif  // SAMPLE_LOCALES_HPP
