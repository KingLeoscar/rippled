//------------------------------------------------------------------------------
/*
    This file is part of Beast: https://github.com/vinniefalco/Beast
    Copyright 2013, Vinnie Falco <vinnie.falco@gmail.com>

    Portions of this file are from JUCE.
    Copyright (c) 2013 - Raw Material Software Ltd.
    Please visit http://www.juce.com

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef BEAST_RANDOM_BEASTHEADER
#define BEAST_RANDOM_BEASTHEADER

#include "beast_BigInteger.h"


//==============================================================================
/**
    A random number generator.

    You can create a Random object and use it to generate a sequence of random numbers.
*/
class BEAST_API Random : LeakChecked <Random>
{
public:
    //==============================================================================
    /** Creates a Random object based on a seed value.

        For a given seed value, the subsequent numbers generated by this object
        will be predictable, so a good idea is to set this value based
        on the time, e.g.

        new Random (Time::currentTimeMillis())
    */
    explicit Random (int64 seedValue) noexcept;

    /** Creates a Random object using a random seed value.
        Internally, this calls setSeedRandomly() to randomise the seed.
    */
    Random();

    /** Destructor. */
    ~Random() noexcept;

    /** Returns the next random 32 bit integer.

        @returns a random integer from the full range 0x80000000 to 0x7fffffff
    */
    int nextInt() noexcept;

    /** Returns the next random number, limited to a given range.
        The maxValue parameter may not be negative, or zero.
        @returns a random integer between 0 (inclusive) and maxValue (exclusive).
    */
    int nextInt (int maxValue) noexcept;

    /** Returns the next 64-bit random number.

        @returns a random integer from the full range 0x8000000000000000 to 0x7fffffffffffffff
    */
    int64 nextInt64() noexcept;

    /** Returns the next random floating-point number.

        @returns a random value in the range 0 to 1.0
    */
    float nextFloat() noexcept;

    /** Returns the next random floating-point number.

        @returns a random value in the range 0 to 1.0
    */
    double nextDouble() noexcept;

    /** Returns the next random boolean value.
    */
    bool nextBool() noexcept;

    /** Returns a BigInteger containing a random number.

        @returns a random value in the range 0 to (maximumValue - 1).
    */
    BigInteger nextLargeNumber (const BigInteger& maximumValue);

    /** Sets a range of bits in a BigInteger to random values. */
    void fillBitsRandomly (BigInteger& arrayToChange, int startBit, int numBits);

    //==============================================================================
    /** Resets this Random object to a given seed value. */
    void setSeed (int64 newSeed) noexcept;

    /** Merges this object's seed with another value.
        This sets the seed to be a value created by combining the current seed and this
        new value.
    */
    void combineSeed (int64 seedValue) noexcept;

    /** Reseeds this generator using a value generated from various semi-random system
        properties like the current time, etc.

        Because this function convolves the time with the last seed value, calling
        it repeatedly will increase the randomness of the final result.
    */
    void setSeedRandomly();

    /** The overhead of creating a new Random object is fairly small, but if you want to avoid
        it, you can call this method to get a global shared Random object.

        It's not thread-safe though, so threads should use their own Random object, otherwise
        you run the risk of your random numbers becoming.. erm.. randomly corrupted..
    */
    static Random& getSystemRandom() noexcept;

private:
    //==============================================================================
    int64 seed;
};


#endif   // BEAST_RANDOM_BEASTHEADER
