#ifndef IGENESIS_H
#define IGENESIS_H
#include <Utils/Standard.h>

// The IGenesisPseudoRegister is meant to simulate a Sega Genesis register (Really just a register in general).
// It has lots of definations to allow access to the register as if it was an integer.
// It's currently a work in progress and is only meant for help with REing not yet completely RE'd functions.

class IGenesisPseudoRegister;

class IGenesisPseudoRegister {
    public:
        IGenesisPseudoRegister() {
        
        }

		IGenesisPseudoRegister(uint8_t newRegValue) {
			pseudoRegister = newRegValue;
		}

		IGenesisPseudoRegister(uint16_t newRegValue) {
			pseudoRegister = newRegValue;
		}
        
        IGenesisPseudoRegister(uint32_t newRegValue) {
			pseudoRegister = newRegValue;
        }
        
		IGenesisPseudoRegister(int8_t newRegValue) {
			pseudoRegister = newRegValue;
		}
        
		IGenesisPseudoRegister(int16_t newRegValue) {
			pseudoRegister = newRegValue;
		}

		IGenesisPseudoRegister(int32_t newRegValue) {
			pseudoRegister = newRegValue;
		}
        
        int32_t operator[](std::size_t idx) { 
            return (int32_t)pseudoRegister; 
        }

		inline int64_t operator+() {
			return +pseudoRegister;
		}

		inline int64_t operator-() {
			return -pseudoRegister;
		}

		inline int64_t operator~() {
			return ~pseudoRegister;
		}

		inline uint32_t operator+(const uint32_t& other) {
			return (uint32_t)(pseudoRegister + other);
		}
		inline int32_t operator+(const int32_t& other) {
			return (int32_t)(pseudoRegister + other);
		}

		inline uint32_t operator-(const uint32_t& other) {
			return (uint32_t)(pseudoRegister - other);
		}
		inline int32_t operator-(const int32_t& other) {
			return (int32_t)(pseudoRegister - other);
		}

		inline uint32_t operator*(const uint32_t& other) {
			return (uint32_t)(pseudoRegister * other);
		}
		inline int32_t operator*(const int32_t& other) {
			return (int32_t)(pseudoRegister * other);
		}

		inline uint32_t operator/(const uint32_t& other) {
			return (uint32_t)(pseudoRegister / other);
		}
		inline int32_t operator/(const int32_t& other) {
			return (int32_t)(pseudoRegister / other);
		}

		inline uint32_t operator%(const uint32_t& other) {
			return (uint32_t)(pseudoRegister % other);
		}
		inline int32_t operator%(const int32_t& other) {
			return (int32_t)(pseudoRegister % other);
		}

		inline uint32_t operator&(const uint32_t& other) {
			return (uint32_t)(pseudoRegister & other);
		}
		inline int32_t operator&(const int32_t& other) {
			return (int32_t)(pseudoRegister & other);
		}

		inline uint32_t operator|(const uint32_t& other) {
			return (uint32_t)(pseudoRegister | other);
		}
		inline int32_t operator|(const int32_t& other) {
			return (int32_t)(pseudoRegister | other);
		}

		inline uint32_t operator^(const uint32_t& other) {
			return (uint32_t)(pseudoRegister ^ other);
		}
		inline int32_t operator^(const int32_t& other) {
			return (int32_t)(pseudoRegister ^ other);
		}

		inline uint32_t operator<<(const uint32_t& other) {
			return (uint32_t)(pseudoRegister << other);
		}
		inline int32_t operator<<(const int32_t& other) {
			return (int32_t)(pseudoRegister << other);
		}

		inline uint32_t operator>>(const uint32_t& other) {
			return (uint32_t)(pseudoRegister >> other);
		}
		inline int32_t operator>>(const int32_t& other) {
			return (int32_t)(pseudoRegister >> other);
		}

		inline uint8_t operator=(const uint8_t& other) {
			if (pseudoRegister != other) {
				pseudoRegister = (uint32_t)other;
			}
			return (uint8_t)pseudoRegister;
		}
		inline uint16_t operator=(const uint16_t& other) {
			if (pseudoRegister != other) {
				pseudoRegister = (uint32_t)other;
			}
			return (uint16_t)pseudoRegister;
		}
        inline uint32_t operator=(const uint32_t& other) {
            if (pseudoRegister != other) { 
                pseudoRegister = other;
            }
            return (uint32_t)pseudoRegister;
        }

		inline int8_t operator=(const int8_t& other) {
			if (pseudoRegister != other) {
				pseudoRegister = other;
			}
			return (int8_t)pseudoRegister;
		}
		inline int16_t operator=(const int16_t& other) {
			if (pseudoRegister != other) {
				pseudoRegister = other;
			}
			return (int16_t)pseudoRegister;
		}
		inline int32_t operator=(const int32_t& other) {
			if (pseudoRegister != other) {
				pseudoRegister = other;
			}
			return (int32_t)pseudoRegister;
		}
        
        inline int32_t operator++() {
            // Actual increment takes place here.
            pseudoRegister++;
            
            return (int32_t)pseudoRegister;
        }
        inline int32_t operator--() {
            // Actual decrement takes place here.
            pseudoRegister--;
            
            return (int32_t)pseudoRegister;
        }

		inline uint32_t operator+=(const uint32_t& rhs) {
			pseudoRegister += rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator+=(const int32_t& rhs) {
			pseudoRegister += rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator-=(const uint32_t& rhs) {
			pseudoRegister -= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator-=(const int32_t& rhs) {
			pseudoRegister -= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator*=(const uint32_t& rhs) {
			pseudoRegister *= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator*=(const int32_t& rhs) {
			pseudoRegister *= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator/=(const uint32_t& rhs) {
			pseudoRegister /= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator/=(const int32_t& rhs) {
			pseudoRegister /= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator%=(const uint32_t& rhs) {
			pseudoRegister %= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator%=(const int32_t& rhs) {
			pseudoRegister %= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator&=(const uint32_t& rhs) {
			pseudoRegister &= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator&=(const int32_t& rhs) {
			pseudoRegister &= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator|=(const uint32_t& rhs) {
			pseudoRegister |= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator|=(const int32_t& rhs) {
			pseudoRegister |= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator^=(const uint32_t& rhs) {
			pseudoRegister ^= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator^=(const int32_t& rhs) {
			pseudoRegister ^= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator<<=(const uint32_t& rhs) {
			pseudoRegister <<= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator<<=(const int32_t& rhs) {
			pseudoRegister <<= rhs;
			return (int32_t)pseudoRegister;
		}

		inline uint32_t operator>>=(const uint32_t& rhs) {
			pseudoRegister >>= rhs;
			return (uint32_t)pseudoRegister;
		}
		inline int32_t operator>>=(const int32_t& rhs) {
			pseudoRegister >>= rhs;
			return (int32_t)pseudoRegister;
		}
        
        inline bool operator< (const uint32_t& rhs) { 
            return pseudoRegister < rhs;
        }
        inline bool operator< (const int32_t& rhs) { 
            return pseudoRegister < rhs;
        }
        
        inline bool operator> (const uint32_t& rhs) { 
            return rhs < pseudoRegister; 
        }
        inline bool operator> (const int32_t& rhs) { 
            return rhs < pseudoRegister;  
        }
        
        inline bool operator<=(const uint32_t& rhs) { 
            return pseudoRegister <= rhs;
        }
        inline bool operator<=(const int32_t& rhs) { 
            return pseudoRegister <= rhs;
        }
        
        inline bool operator>=(const uint32_t& rhs) { 
            return pseudoRegister >= rhs; 
        }
        inline bool operator>=(const int32_t& rhs) { 
            return pseudoRegister >= rhs;
        }
        
        inline bool operator==(const uint32_t& rhs) {
            return pseudoRegister == rhs;
        }
        inline bool operator==(const int32_t& rhs) { 
            return pseudoRegister == rhs;
        }

		inline bool operator!=(const uint32_t& rhs) {
			return pseudoRegister != rhs;
		}
		inline bool operator!=(const int32_t& rhs) {
			return pseudoRegister != rhs;
		}
        
        inline uint8_t u8() {
            return (uint8_t)pseudoRegister;
        }
        
        inline uint16_t u16() {
            return (uint16_t)pseudoRegister;
        }
        
        inline uint32_t u32() {
            return (uint32_t)pseudoRegister;
        }
        
        inline int8_t s8() {
            return (int8_t)pseudoRegister;
        }
        
        inline int16_t s16() {
            return (int16_t)pseudoRegister;
        }
        
        inline int32_t s32() {
            return (int32_t)pseudoRegister;
        }

	protected:
		int64_t pseudoRegister = 0x00000000;
};

static IGenesisPseudoRegister GenesisPsuedoRegisters[14] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                                             0x00000000, 0x00000000, 0x00000000, 0x00000000 };

#ifndef D1
#define D1 GenesisPsuedoRegisters[0]
#define D2 GenesisPsuedoRegisters[1]
#define D3 GenesisPsuedoRegisters[2]
#define D4 GenesisPsuedoRegisters[3]
#define D5 GenesisPsuedoRegisters[4]
#define D6 GenesisPsuedoRegisters[5]
#define D7 GenesisPsuedoRegisters[6]
#endif

#ifndef A1
#define A1 GenesisPsuedoRegisters[7]
#define A2 GenesisPsuedoRegisters[8]
#define A3 GenesisPsuedoRegisters[9]
#define A4 GenesisPsuedoRegisters[10]
#define A5 GenesisPsuedoRegisters[11]
#define A6 GenesisPsuedoRegisters[12]
#define A7 GenesisPsuedoRegisters[13]
#endif

#endif