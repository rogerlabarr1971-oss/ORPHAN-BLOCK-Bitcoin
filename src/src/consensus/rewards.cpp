ORPH Reward Allocator Engine Implementation
File: src/consensus/rewards.cpp

This file contains the implementation of the economic model for ORPHAN BLOCK Bitcoin,
specifically handling the 75%/25% subsidy split between Winner and Uncle miners.
#include "rewards.h"
#include "../transaction.h"
#include <iostream>
#include <algorithm>
#include <vector>
// --- Configuration Constants (Assumed to be loaded from config.json) ---
// These values would be loaded into the C++ runtime environment during node startup.
// Placeholder values for configuration (loaded at runtime)
const uint64_t INITIAL_SUBSIDY = 5000000000; // 50 ORPH (in satoshis)
const double UNCLE_SUBSIDY_RATIO = 0.25;      // 25% of subsidy goes to uncles
const double WINNER_FEE_RATIO = 0.50;         // 50% of fees goes to winner
// --- Placeholder for Fee Calculation ---
/**
 * @brief Calculates the total transaction fees included in a block.
 * @param block The block object containing the transactions.
 * @return The total fees (sum of input values - sum of output values) in satoshis.
   */
   static uint64_t CalculateTotalFees(const CBlock& block) {
   // NOTE: This implementation is complex in real Bitcoin forks; this is a placeholder.
   uint64_t total_fees = 0;
   // ... logic to sum up all transaction fees in the block
   std::cout << "DEBUG: Calculating total fees." << std::endl;
   return total_fees; // Placeholder value
   }
// --- Reward Allocation Implementation ---
/**
 * @brief Allocates the total block reward (subsidy + fees) and creates the Coinbase Transaction.
 *  * This function enforces the Uncle Reward Split rule and creates the specific
 * transaction outputs for the winning miner and the uncle pool.
 *  * @param block The newly validated CBlock object.
 * @param winner_address The address of the miner who found this block.
 * @param uncle_miner_addresses A list of addresses for the miners whose blocks were included as uncles.
 * @return A fully constructed Coinbase transaction ready to be included in the block.
   */
   CTransaction RewardAllocator::AllocateRewardsToMiners(
   const CBlock& block,
   const CKeyID& winner_address,
   const std::vector<CKeyID>& uncle_miner_addresses)
   {
   // 1. Calculate the Total Reward Pot
   const uint64_t total_fees = CalculateTotalFees(block);
   const uint64_t current_subsidy = INITIAL_SUBSIDY; // NOTE: Needs to adjust for halving rules
   const uint64_t total_reward_pot = current_subsidy + total_fees;
   std::cout << "Total Reward Pot calculated: " << total_reward_pot << " satoshis." << std::endl;
   // 2. Determine Subsidy Split (75% Winner / 25% Uncles)
   const uint64_t uncle_subsidy = (uint64_t)(current_subsidy * UNCLE_SUBSIDY_RATIO);
   const uint64_t winner_subsidy = current_subsidy - uncle_subsidy;
   // 3. Determine Fee Split (50% Winner / 50% Uncles)
   const uint64_t winner_fees = (uint64_t)(total_fees * WINNER_FEE_RATIO);
   const uint64_t uncle_fees = total_fees - winner_fees;
   // --- FINAL REWARD AMOUNTS ---
   const uint64_t winner_total_reward = winner_subsidy + winner_fees;
   const uint64_t uncle_pool_reward = uncle_subsidy + uncle_fees;
   // 4. Create the Coinbase Transaction
   CTransaction coinbase_tx;
   // Coinbase transactions have a single empty input
   coinbase_tx.vin.emplace_back();
   // 5. Create the WINNER Output (Address and Amount)
   CTxOut winner_output;
   winner_output.nValue = winner_total_reward;
   // winner_output.scriptPubKey = GetScriptForDestination(winner_address); // Placeholder function
   coinbase_tx.vout.push_back(winner_output);
   std::cout << "WINNER Reward Output created: " << winner_total_reward << " satoshis." << std::endl;
   // 6. Distribute the UNCLE Reward Pool
   // The total uncle_pool_reward must be divided among all eligible uncle_miner_addresses.
   if (!uncle_miner_addresses.empty()) {
   const uint64_t reward_per_uncle = uncle_pool_reward / uncle_miner_addresses.size();
   const uint64_t remainder = uncle_pool_reward % uncle_miner_addresses.size(); // To be added to the first uncle
    for (size_t i = 0; i < uncle_miner_addresses.size(); ++i) {
     uint64_t reward = reward_per_uncle;
     if (i == 0) {
         reward += remainder; // Add remainder to the first uncle miner for precision
     }

     CTxOut uncle_output;
     uncle_output.nValue = reward;
     // uncle_output.scriptPubKey = GetScriptForDestination(uncle_miner_addresses[i]); // Placeholder function
     coinbase_tx.vout.push_back(uncle_output);
 }
 std::cout << "UNCLE Reward Pool distributed to " << uncle_miner_addresses.size() << " miners." << std::endl;

   }
   // 7. Final Sanity Check (Total inputs must match total outputs)
   // assert(total_reward_pot == sum_of_all_tx_outputs); // Final check placeholder
   // 8. Sign and Finalize (Placeholder)
   // coinbase_tx.Finalize(); // Placeholder
   return coinbase_tx;
   }
