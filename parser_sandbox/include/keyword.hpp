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
#ifndef OCCA_LANG_KEYWORD_HEADER
#define OCCA_LANG_KEYWORD_HEADER

#include "trie.hpp"

namespace occa {
  namespace lang {
    class keyword_t;
    class qualifier;
    class primitiveType;
    class type_t;
    class functionType;

    namespace keywordType {
      extern const int none;
      extern const int qualifier;
      extern const int primitiveType;

      extern const int type;
      extern const int function;

      extern const int if_;
      extern const int else_;
      extern const int switch_;
      extern const int conditional;

      extern const int case_;
      extern const int default_;
      extern const int switchLabel;

      extern const int for_;
      extern const int while_;
      extern const int do_;
      extern const int iteration;

      extern const int break_;
      extern const int continue_;
      extern const int return_;
      extern const int goto_;
      extern const int jump;

      extern const int statement;
    }

    class keyword_t {
    public:
      void *ptr;
      std::string name;
      int kType;

      keyword_t();
      keyword_t(const qualifier &value);
      keyword_t(const primitiveType &value);
      keyword_t(type_t &type);
      keyword_t(functionType &type);
      keyword_t(void *ptr_,
                const std::string &name_,
                const int kType_);

      void free();

      template <class TM>
      inline TM& to() {
        return *((TM*) ptr);
      }

      template <class TM>
      inline const TM& to() const {
        return *((TM*) ptr);
      }
    };

    typedef trie<keyword_t> keywordTrie;

    void getKeywords(keywordTrie &keywords);

    template <class TM>
    void addKeyword(keywordTrie &keywords,
                    const TM &value) {
      keyword_t keyword(value);
      keywords.add(keyword.name, keyword);
    }

    void addKeyword(keywordTrie &keywords,
                    const std::string &name,
                    const int kType);

    void freeKeywords(keywordTrie &keywords);
  }
}
#endif
