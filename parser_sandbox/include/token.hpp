/* The MIT License (MIT)
 *
 * Copyright (c) 2014-2018 David Medina and Tim Warburton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 */
#ifndef OCCA_PARSER_TOKEN_HEADER2
#define OCCA_PARSER_TOKEN_HEADER2

#include "occa/tools/io.hpp"

#include "trie.hpp"
#include "file.hpp"
#include "type.hpp"

namespace occa {
  namespace lang {
    class operator_t;
    class token_t;

    typedef trie<const operator_t*> operatorTrie;
    typedef std::vector<token_t*> tokenVector;

    namespace charcodes {
      extern const char whitespace[];
      extern const char whitespaceNoNewline[];
      extern const char alpha[];
      extern const char number[];
      extern const char alphanumber[];
      extern const char identifierStart[];
      extern const char identifier[];
      extern const char operators[];
    }

    operatorTrie& getOperators();

    namespace encodingType {
      extern const int none;
      extern const int R;
      extern const int u8;
      extern const int u;
      extern const int U;
      extern const int L;
      extern const int ux;
      extern const int bits;
    }

    namespace tokenType {
      extern const int none;
      extern const int unknown;

      extern const int newline;

      extern const int identifier;

      extern const int systemHeader;
      extern const int header;

      extern const int primitive;
      extern const int op;

      extern const int char_;
      extern const int string;
      extern const int withUDF;
      extern const int withEncoding;
      extern const int encodingShift;

      int getEncoding(const int type);
      int mergeEncodings(const int type1, const int type2);
    }

    class token_t : public errorHandler {
    public:
      fileOrigin origin;

      token_t(const fileOrigin &origin_);

      virtual ~token_t();

      template <class TM>
      inline bool is() const {
        return (dynamic_cast<const TM*>(this) != NULL);
      }

      template <class TM>
      inline TM& to() {
        TM *ptr = dynamic_cast<TM*>(this);
        OCCA_ERROR("Unable to cast token_t::to",
                   ptr != NULL);
        return *ptr;
      }

      template <class TM>
      inline const TM& to() const {
        const TM *ptr = dynamic_cast<const TM*>(this);
        OCCA_ERROR("Unable to cast token_t::to",
                   ptr != NULL);
        return *ptr;
      }

      static int safeType(token_t *token);

      virtual int type() const = 0;

      virtual token_t* clone() = 0;

      virtual void print(std::ostream &out) const = 0;

      void preprint(std::ostream &out);
      void postprint(std::ostream &out);

      std::string str() const;
    };

    //---[ Unknown ]--------------------
    class unknownToken : public token_t {
    public:
      char symbol;

      unknownToken(const fileOrigin &origin_);

      virtual ~unknownToken();

      virtual int type() const;

      virtual token_t* clone();

      virtual void print(std::ostream &out) const;
    };
    //==================================

    //---[ Newline ]--------------------
    class newlineToken : public token_t {
    public:
      newlineToken(const fileOrigin &origin_);

      virtual ~newlineToken();

      virtual int type() const;

      virtual token_t* clone();

      virtual void print(std::ostream &out) const;
    };
    //==================================

    //---[ Identifier ]-----------------
    class identifierToken : public token_t {
    public:
      std::string value;

      identifierToken(const fileOrigin &origin_,
                      const std::string &value_);

      virtual ~identifierToken();

      virtual int type() const;

      virtual token_t* clone();

      virtual void print(std::ostream &out) const;
    };
    //==================================

    //---[ Primitive ]------------------
    class primitiveToken : public token_t {
    public:
      primitive value;
      std::string strValue;

      primitiveToken(const fileOrigin &origin_,
                     const primitive &value_,
                     const std::string &strValue_);

      virtual ~primitiveToken();

      virtual int type() const;

      virtual token_t* clone();

      virtual void print(std::ostream &out) const;
    };
    //==================================

    //---[ Operator ]-------------------
    class operatorToken : public token_t {
    public:
      const operator_t &op;

      operatorToken(const fileOrigin &origin_,
                    const operator_t &op_);

      virtual ~operatorToken();

      virtual int type() const;

      virtual token_t* clone();

      virtual void print(std::ostream &out) const;
    };
    //==================================

    //---[ Char ]-----------------------
    class charToken : public token_t {
    public:
      int encoding;
      std::string value;
      std::string udf;

      charToken(const fileOrigin &origin_,
                int encoding_,
                const std::string &value_,
                const std::string &udf_);

      virtual ~charToken();

      virtual int type() const;

      virtual token_t* clone();

      virtual void print(std::ostream &out) const;
    };
    //==================================

    //---[ String ]---------------------
    class stringToken : public token_t {
    public:
      int encoding;
      std::string value;
      std::string udf;

      stringToken(const fileOrigin &origin_,
                  const std::string &value_);

      stringToken(const fileOrigin &origin_,
                  int encoding_,
                  const std::string &value_,
                  const std::string &udf_);

      virtual ~stringToken();

      virtual int type() const;

      virtual token_t* clone();

      void append(const stringToken &token);

      virtual void print(std::ostream &out) const;
    };
    //==================================

    //---[ Header ]---------------------
    class headerToken : public token_t {
    public:
      bool systemHeader;
      std::string value;

      headerToken(const fileOrigin &origin_,
                  const bool systemHeader_,
                  const std::string &value_);

      virtual ~headerToken();

      virtual int type() const;

      virtual token_t* clone();

      virtual void print(std::ostream &out) const;
    };
    //==================================
  }
}

#endif