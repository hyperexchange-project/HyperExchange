/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <graphene/chain/protocol/asset.hpp>
#include <graphene/db/object.hpp>
#include <graphene/db/generic_index.hpp>
#include <map>
namespace graphene { namespace chain {
   using namespace graphene::db;

   class miner_object;

   class miner_object : public abstract_object<miner_object>
   {
      public:
         static const uint8_t space_id = protocol_ids;
         static const uint8_t type_id = miner_object_type;

         account_id_type  miner_account;
         uint64_t         last_aslot = 0;
         public_key_type  signing_key;
		 uint32_t		  last_change_signing_key_block_num = 0;
         optional< vesting_balance_id_type > pay_vb;
         vote_id_type     vote_id;
         uint64_t         total_votes = 0;
         string           url;
         int64_t          total_missed = 0;
		 int64_t		  total_produced = 0;
         uint32_t         last_confirmed_block_num = 0;
		 //std::map<string, vector<asset>> lockbalance;
		 std::map<string,asset> lockbalance_total;
		 share_type       pledge_weight = 100;
		 uint8_t		  participation_rate = 100;

		 optional<SecretHashType>        next_secret_hash;

		 miner_object() : vote_id(vote_id_type::witness) {}
   };

   struct by_account;
   struct by_vote_id;
   struct by_last_block;
   using miner_multi_index_type = multi_index_container<
      miner_object,
      indexed_by<
         ordered_unique< tag<by_id>,
            member<object, object_id_type, &object::id>
         >,
         ordered_unique< tag<by_account>,
            member<miner_object, account_id_type, &miner_object::miner_account>
         >,
         ordered_unique< tag<by_vote_id>,
            member<miner_object, vote_id_type, &miner_object::vote_id>
         >
      >
   >;
   using miner_index = generic_index<miner_object, miner_multi_index_type>;
} } // graphene::chain

FC_REFLECT_DERIVED( graphene::chain::miner_object, (graphene::db::object),
                    (miner_account)
                    (last_aslot)
                    (signing_key)
					(last_change_signing_key_block_num)
                    (pay_vb)
                    (vote_id)
                    (total_votes)
                    (url) 
                    (total_missed)
					(lockbalance_total)
					(total_produced)
                    (last_confirmed_block_num)
					(pledge_weight)
					(participation_rate)
					(next_secret_hash)
                  )
