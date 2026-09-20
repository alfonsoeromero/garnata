/*
 * VariableByteCoder.h - The Garnata Retrieval System
 * Copyright (C) 2005, 2026 Alfonso E. Romero
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _VARIABLE_BYTE_CODER_
#define _VARIABLE_BYTE_CODER_

#include "CompressionAlgorithm.h"

using namespace std;

class VariableByteCoder : public CompressionAlgorithm
{
    public:
    /**  Compress an unsigned into a byte buffer
    @param u unsigned to compress
    @param buff binary buffer
    @param num number of occupied bytes    
    */
    void compressUnsigned(unsigned u, char* buff, unsigned& num);

    /**  Compress a long into a byte buffer
    @param l long to compress
    @param buff binary buffer
    @param num number of occupied bytes    
    */
    void compressLong(long l, char* buff, unsigned& num);

    /**  Compress a float into a byte buffer
    @param f float to compress
    @param buff binary buffer
    @param num number of occupied bytes    
    */
    void compressFloat(float f, char* buff, unsigned& num);

    /**  Deflates a float from a byte buffer
    @param f float to deflate
    @param buff binary buffer
    */
    void deflateFloat(float& f, BasicInputBinaryBuffer& buff);
    
    /**  Deflates an unsigned from a byte buffer
    @param u unsigned to deflate
    @param buff binary buffer
    */
    void deflateUnsigned(unsigned& u, BasicInputBinaryBuffer& buff);

    /**  Deflates a long into a byte buffer
    @param l long to deflate
    @param buff binary buffer
    */
    void deflateLong(long& l, BasicInputBinaryBuffer& buff);
  
};

#endif

