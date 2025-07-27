#pragma once

#include <cstdint>

namespace Flags {

    // 8-bit flags
    enum Flag8 : uint8_t {
        FlagClear = 0x00,
        Flag1 = 0x01,
        Flag2 = 0x02,
        Flag3 = 0x04,
        Flag4 = 0x08,
        Flag5 = 0x10,
        Flag6 = 0x20,
        Flag7 = 0x40,
        Flag8 = 0x80,
        FlagAll = 0xFF
    };

    // 16-bit flags
    enum Flag16 : uint16_t {
        FlagClear = 0x0000,
        Flag1 = 0x0001,
        Flag2 = 0x0002,
        Flag3 = 0x0004,
        Flag4 = 0x0008,
        Flag5 = 0x0010,
        Flag6 = 0x0020,
        Flag7 = 0x0040,
        Flag8 = 0x0080,
        Flag9 = 0x0100,
        Flag10 = 0x0200,
        Flag11 = 0x0400,
        Flag12 = 0x0800,
        Flag13 = 0x1000,
        Flag14 = 0x2000,
        Flag15 = 0x4000,
        Flag16 = 0x8000,
        FlagAll = 0xFFFF
    };

    // 32-bit flags
    enum Flag32 : uint32_t {
        FlagClear = 0x00000000,
        Flag1 = 0x00000001,
        Flag2 = 0x00000002,
        Flag3 = 0x00000004,
        Flag4 = 0x00000008,
        Flag5 = 0x00000010,
        Flag6 = 0x00000020,
        Flag7 = 0x00000040,
        Flag8 = 0x00000080,
        Flag9 = 0x00000100,
        Flag10 = 0x00000200,
        Flag11 = 0x00000400,
        Flag12 = 0x00000800,
        Flag13 = 0x00001000,
        Flag14 = 0x00002000,
        Flag15 = 0x00004000,
        Flag16 = 0x00008000,
        Flag17 = 0x00010000,
        Flag18 = 0x00020000,
        Flag19 = 0x00040000,
        Flag20 = 0x00080000,
        Flag21 = 0x00100000,
        Flag22 = 0x00200000,
        Flag23 = 0x00400000,
        Flag24 = 0x00800000,
        Flag25 = 0x01000000,
        Flag26 = 0x02000000,
        Flag27 = 0x04000000,
        Flag28 = 0x08000000,
        Flag29 = 0x10000000,
        Flag30 = 0x20000000,
        Flag31 = 0x40000000,
        Flag32 = 0x80000000,
        FlagAll = 0xFFFFFFFF
    };

    // 64-bit flags (rare)
    enum Flag64 : uint64_t {
        FlagClear = 0x0000000000000000ULL,
        Flag1 = 0x0000000000000001ULL,
        Flag2 = 0x0000000000000002ULL,
        Flag3 = 0x0000000000000004ULL,
        Flag4 = 0x0000000000000008ULL,
        Flag5 = 0x0000000000000010ULL,
        Flag6 = 0x0000000000000020ULL,
        Flag7 = 0x0000000000000040ULL,
        Flag8 = 0x0000000000000080ULL,
        Flag9 = 0x0000000000000100ULL,
        Flag10 = 0x0000000000000200ULL,
        Flag11 = 0x0000000000000400ULL,
        Flag12 = 0x0000000000000800ULL,
        Flag13 = 0x0000000000001000ULL,
        Flag14 = 0x0000000000002000ULL,
        Flag15 = 0x0000000000004000ULL,
        Flag16 = 0x0000000000008000ULL,
        Flag17 = 0x0000000000010000ULL,
        Flag18 = 0x0000000000020000ULL,
        Flag19 = 0x0000000000040000ULL,
        Flag20 = 0x0000000000080000ULL,
        Flag21 = 0x0000000000100000ULL,
        Flag22 = 0x0000000000200000ULL,
        Flag23 = 0x0000000000400000ULL,
        Flag24 = 0x0000000000800000ULL,
        Flag25 = 0x0000000001000000ULL,
        Flag26 = 0x0000000002000000ULL,
        Flag27 = 0x0000000004000000ULL,
        Flag28 = 0x0000000008000000ULL,
        Flag29 = 0x0000000010000000ULL,
        Flag30 = 0x0000000020000000ULL,
        Flag31 = 0x0000000040000000ULL,
        Flag32 = 0x0000000080000000ULL,
        Flag33 = 0x0000000100000000ULL,
        Flag34 = 0x0000000200000000ULL,
        Flag35 = 0x0000000400000000ULL,
        Flag36 = 0x0000000800000000ULL,
        Flag37 = 0x0000001000000000ULL,
        Flag38 = 0x0000002000000000ULL,
        Flag39 = 0x0000004000000000ULL,
        Flag40 = 0x0000008000000000ULL,
        Flag41 = 0x0000010000000000ULL,
        Flag42 = 0x0000020000000000ULL,
        Flag43 = 0x0000040000000000ULL,
        Flag44 = 0x0000080000000000ULL,
        Flag45 = 0x0000100000000000ULL,
        Flag46 = 0x0000200000000000ULL,
        Flag47 = 0x0000400000000000ULL,
        Flag48 = 0x0000800000000000ULL,
        Flag49 = 0x0001000000000000ULL,
        Flag50 = 0x0002000000000000ULL,
        Flag51 = 0x0004000000000000ULL,
        Flag52 = 0x0008000000000000ULL,
        Flag53 = 0x0010000000000000ULL,
        Flag54 = 0x0020000000000000ULL,
        Flag55 = 0x0040000000000000ULL,
        Flag56 = 0x0080000000000000ULL,
        Flag57 = 0x0100000000000000ULL,
        Flag58 = 0x0200000000000000ULL,
        Flag59 = 0x0400000000000000ULL,
        Flag60 = 0x0800000000000000ULL,
        Flag61 = 0x1000000000000000ULL,
        Flag62 = 0x2000000000000000ULL,
        Flag63 = 0x4000000000000000ULL,
        Flag64 = 0x8000000000000000ULL,
        FlagAll = 0xFFFFFFFFFFFFFFFFULL
    };

    struct Flag8State {
        uint8_t Flags; // 8-bit flags to represent various states
        Flag8State() : Flags(Flag8::FlagClear) {} // Initialize with no flags set
        void SetFlag(Flag8 flag) {
            Flags |= flag; // Set the specified flag
        }
        void ClearFlag(Flag8 flag) {
            Flags &= ~flag; // Clear the specified flag
        }
        bool IsFlagSet(Flag8 flag) const {
            return (Flags & flag) != 0; // Check if the specified flag is set
        }
        void ToggleFlag(Flag8 flag) {
            Flags ^= flag; // Toggle the specified flag
        }
    };

    struct Flag16State {
        uint16_t Flags; // 16-bit flags to represent various states
        Flag16State() : Flags(Flag16::FlagClear) {} // Initialize with no flags set
        void SetFlag(Flag16 flag) {
            Flags |= flag; // Set the specified flag
        }
        void ClearFlag(Flag16 flag) {
            Flags &= ~flag; // Clear the specified flag
        }
        bool IsFlagSet(Flag16 flag) const {
            return (Flags & flag) != 0; // Check if the specified flag is set
        }
        void ToggleFlag(Flag16 flag) {
            Flags ^= flag; // Toggle the specified flag
        }
    };

    struct Flag32State {
        uint32_t Flags; // 32-bit flags to represent various states
        Flag32State() : Flags(Flag32::FlagClear) {} // Initialize with no flags set
        void SetFlag(Flag32 flag) {
            Flags |= flag; // Set the specified flag
        }
        void ClearFlag(Flag32 flag) {
            Flags &= ~flag; // Clear the specified flag
        }
        bool IsFlagSet(Flag32 flag) const {
            return (Flags & flag) != 0; // Check if the specified flag is set
        }
        void ToggleFlag(Flag32 flag) {
            Flags ^= flag; // Toggle the specified flag
        }
    };

    struct Flag64State {
        uint64_t Flags; // 64-bit flags to represent various states
        Flag64State() : Flags(Flag64::FlagClear) {} // Initialize with no flags set
        void SetFlag(Flag64 flag) {
            Flags |= flag; // Set the specified flag
        }
        void ClearFlag(Flag64 flag) {
            Flags &= ~flag; // Clear the specified flag
        }
        bool IsFlagSet(Flag64 flag) const {
            return (Flags & flag) != 0; // Check if the specified flag is set
        }
        void ToggleFlag(Flag64 flag) {
            Flags ^= flag; // Toggle the specified flag
        }
    };
} // namespace Flags