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

#ifndef OCCA_LANG_BUILTINS_TRANSFORMS_TILE_HEADER
#define OCCA_LANG_BUILTINS_TRANSFORMS_TILE_HEADER

#include "statementTransform.hpp"
#include "builtins/transforms/variableReplacer.hpp"

namespace occa {
  namespace lang {
    namespace transforms {
      class tile : public statementTransform {
      public:
        variableReplacer_t variableReplacer;

        tile();

        bool isValidInit(statement_t &smnt);

        bool isValidCheck(variable_t &var,
                          statement_t &smnt);

        bool isValidUpdate(variable_t &var,
                           statement_t &smnt);

        bool sameVariable(variable_t &var,
                          leftUnaryOpNode &opNode);

        bool sameVariable(variable_t &var,
                          rightUnaryOpNode &opNode);

        int sameVariable(variable_t &var,
                         binaryOpNode &opNode);

        virtual statement_t* transformStatement(statement_t &smnt);

        void setupNewForStatements(attributeToken_t &attr,
                                   forStatement &forSmnt,
                                   variable_t &iter,
                                   variable_t &blockIter,
                                   forStatement &blockForSmnt,
                                   forStatement &innerForSmnt);

        void setupBlockForStatement(exprNode &tileSize,
                                    variable_t &blockIter,
                                    forStatement &blockForSmnt,
                                    forStatement &innerForSmnt);

        void setupInnerForStatement(exprNode &tileSize,
                                    variable_t &iter,
                                    variable_t &blockIter,
                                    forStatement &blockForSmnt,
                                    forStatement &innerForSmnt);

        void setupSafeStatement(attributeToken_t &attr,
                                variable_t &iter,
                                variable_t &blockIter,
                                forStatement &blockForSmnt,
                                forStatement &innerForSmnt);
      };

      bool applyTileTransforms(statement_t &smnt);
    }
  }
}

#endif