import itertools

# Hand strength ranking
HAND_STRENGTH = {
    "High Card": 0, "One Pair": 1, "Two Pair": 2, "Three of a Kind": 3,
    "Straight": 4, "Flush": 5, "Full House": 6, "Four of a Kind": 7,
    "Straight Flush": 8, "Royal Flush": 9
}

def rank_five_card_hand(cards):
    """ Assigns a ranking score to a given 5-card hand. """
    suits = [c[1] for c in cards]
    values = sorted([c[0] for c in cards], reverse=True)

    # Check for flush
    is_flush = all(s == suits[0] for s in suits)

    # Check for straight
    is_straight = values == list(range(values[0], values[0] - 5, -1))

    if is_flush and is_straight:
        return HAND_STRENGTH["Straight Flush"] if values[0] < 14 else HAND_STRENGTH["Royal Flush"]
    elif is_flush:
        return HAND_STRENGTH["Flush"]
    elif is_straight:
        return HAND_STRENGTH["Straight"]
    
    # Count occurrences of each rank
    counts = {v: values.count(v) for v in set(values)}
    count_values = sorted(counts.values(), reverse=True)

    if count_values == [4, 1]:
        return HAND_STRENGTH["Four of a Kind"]
    elif count_values == [3, 2]:
        return HAND_STRENGTH["Full House"]
    elif count_values == [3, 1, 1]:
        return HAND_STRENGTH["Three of a Kind"]
    elif count_values == [2, 2, 1]:
        return HAND_STRENGTH["Two Pair"]
    elif count_values == [2, 1, 1, 1]:
        return HAND_STRENGTH["One Pair"]
    else:
        return HAND_STRENGTH["High Card"]

# Generate flush table
flush_table = {}
for hand in itertools.combinations(range(2, 15), 5):
    flush_key = sum(1 << (h - 2) for h in hand)  # Bitmask encoding for flushes
    flush_table[flush_key] = rank_five_card_hand([(h, 's') for h in hand])

# Generate non-flush table
noflush_table = {}
for hand in itertools.combinations(range(2, 15), 5):
    rank_counts = [hand.count(h) for h in hand]
    hash_key = tuple(sorted(rank_counts, reverse=True))  # Unique hash key
    noflush_table[hash_key] = rank_five_card_hand([(h, 'x') for h in hand])

# Save to a C++ file
with open("hand_lookup_tables.cpp", "w") as f:
    f.write("#include \"HandEvaluator.hpp\"\n\n")
    
    # Write FLUSH_TABLE
    f.write("int FLUSH_TABLE[8192] = {\n    ")
    f.write(", ".join(str(flush_table.get(k, 0)) for k in range(8192)))
    f.write("\n};\n\n")

    # Write NOFLUSH_TABLE
    f.write("int NOFLUSH_TABLE[1000000] = {\n    ")
    f.write(", ".join(str(noflush_table.get(k, 0)) for k in range(1000000)))
    f.write("\n};\n")

print("C++ lookup tables generated successfully in hand_lookup_tables.cpp!")

