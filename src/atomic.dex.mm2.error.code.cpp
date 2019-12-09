/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#include "atomic.dex.mm2.error.code.hpp"

namespace {

    class mm2_error_category_impl : public std::error_category {
    public:
        [[nodiscard]] const char *name() const noexcept override;

        [[nodiscard]] std::string message(int code) const noexcept override;
    };

    const char *mm2_error_category_impl::name() const noexcept {
        return "mm2";
    }

    std::string mm2_error_category_impl::message(int code) const noexcept {
        switch (static_cast<mm2_error>(code)) {
            case mm2_error::success:
                return "";
            case mm2_error::balance_of_a_non_enabled_coin:
                return "You try to retrieve the balance of an unactivated coin";
            case mm2_error::unknown_error:
                return "Unknown error happened";
            case mm2_error::tx_history_of_a_non_enabled_coin:
                return "You try to retrieve the transaction history of an unactivated coin";
            case mm2_error::rpc_withdraw_error:
                return "An RPC error occur when processing the withdraw request, please check your request or the application log.";
            case mm2_error::rpc_send_raw_transaction_error:
                return "An RPC error occur when processing the send_raw_transaction request, please check your tx_hex or the application log.";
        }
    }

    const mm2_error_category_impl err_categ{};
}

std::error_code make_error_code(mm2_error error) noexcept {
    return {static_cast<int>(error), err_categ};
}