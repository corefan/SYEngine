/*
 *      Copyright (C) 2010-2014 Hendrik Leppkes
 *      http://www.1f0.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Initial design and concept by Gabest and the MPC-HC Team, copyright under GPLv2
 */

#ifndef ___LAV_BYTE_PARSER_H___
#define ___LAV_BYTE_PARSER_H___

struct GetBitContext;

/**
* Byte Parser Utility Class
*/
class CByteParser
{
public:
  /** Construct a Byte Parser to parse the given BYTE array with the given length */
  CByteParser(const unsigned char *pData, size_t length);
  virtual ~CByteParser();

  /** Read 1 to 32 Bits from the Byte Array. If peek is set, the data will just be returned, and the buffer not advanced. */
  unsigned int BitRead(unsigned int numBits, bool peek = false);

  /** Read a unsigned number in Exponential Golomb encoding (with k = 0) */
  unsigned int UExpGolombRead();
  /** Read a signed number in Exponential Golomb encoding (with k = 0) */
  int SExpGolombRead();

  /** Pointer to the start of the byte array */
  const unsigned char *Start() const { return m_pData; }
  /** Pointer to the end of the byte array */
  const unsigned char *End() const { return m_pEnd; }

  /** Overall length (in bytes) of the byte array */
  size_t Length() const;

  size_t Pos() const;

  /** Number of bytes remaining in the array */
  size_t Remaining() const { return RemainingBits() >> 3; }

  /** Number of bits remaining */
  size_t RemainingBits() const;

  void BitByteAlign();

private:
  GetBitContext *m_gbCtx = nullptr;

  const unsigned char *m_pData    = nullptr;
  const unsigned char *m_pEnd     = nullptr;
};

#endif //___LAV_BYTE_PARSER_H___