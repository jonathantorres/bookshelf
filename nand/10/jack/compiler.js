import path from 'node:path';
import * as fs from 'node:fs/promises';

import { Tokenizer, TokenType, Keyword } from './tokenizer.js';

export class Compiler {
    #locations = [];

    constructor(locations) {
        this.#locations = locations;
    }

    async compile() {
        // no path/location provided, use the current directory
        if (this.#locations.length === 0) {
            this.#locations.push(process.cwd());
        }

        for (const location of this.#locations) {
            const currentPath = path.parse(location);

            // location is just a single file
            if (currentPath.ext) {
                this.#compileAndSaveFile(location);
                continue;
            }

            // location is a directory of jack files
            let jackFiles = [];

            // open directory and get all of the jack files
            try {
                const files = await fs.readdir(location);

                for (const file of files) {
                    const currentFilePath = path.parse(file);

                    if (currentFilePath.ext === '.jack') {
                        jackFiles.push(file);
                    }
                }
            } catch (err) {
                throw new Error(`${e.message}`);
            }

            if (jackFiles.length === 0) {
                throw new Error(`No Jack files to translate in ${location}`);
            }

            let progLocation = location;

            // make sure program location ends with /
            if (!progLocation.endsWith('/')) {
                progLocation += '/';
            }

            for (const file of jackFiles) {
                await this.#compileAndSaveFile(progLocation + file);
            }
        }
    }

    async #compileAndSaveFile(filePath) {
        const tree = await this.#compileFile(filePath, false);

        // create destination file with parse tree in XML
        const fileElements = path.parse(filePath);
        const destFilePath =
            fileElements.dir + '/' + fileElements.name + '.xml';

        try {
            const handle = await fs.open(destFilePath, 'w+');
            await fs.writeFile(handle, tree);
            handle.close();
        } catch (e) {
            throw new Error(`${e.message}`);
        }
    }

    async #compileFile(filePath, tokenize) {
        const fileElements = path.parse(filePath);

        // make sure the extension is "jack"
        if (fileElements.ext !== '.jack') {
            throw new Error(`Invalid file extension: ${fileElements.ext}`);
        }

        // make sure the first letter of the name of the file is uppercase
        if (fileElements.name[0] !== fileElements.name[0].toUpperCase()) {
            throw new Error(
                `Error: The first character of the file name must be uppercase: ${fileElements.name}`
            );
        }

        // create tokenized file?
        if (tokenize) {
            await this.#tokenizeFile(filePath);
        }

        const tokenizer = new Tokenizer(filePath);
        await tokenizer.init();
        const tree = this.#compileClass(tokenizer);

        return tree;
    }

    #compileClass(tok) {
        let output = '<class>\n';

        tok.advance();
        let tokenType = tok.tokenType();

        if (tokenType !== TokenType.KEYWORD) {
            throw new Error(
                `class keyword not found: ${tokenType.description}`
            );
        }

        output += this.#compileKeyword(tok);

        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.IDENTIFIER) {
            throw new Error(`class name not found: ${tokenType.description}`);
        }

        output += this.#compileIdentifier(tok);

        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(
                `opening brace not found, found: ${tokenType.description}`
            );
        }

        output += this.#compileSymbol(tok);

        while (true) {
            tok.advance();
            tokenType = tok.tokenType();

            if (tokenType === TokenType.KEYWORD) {
                const keyType = tok.keywordType();

                if (keyType === Keyword.STATIC || keyType === Keyword.FIELD) {
                    output += this.#compileClassVarDec(tok);
                    continue;
                }

                if (
                    keyType === Keyword.CONSTRUCTOR ||
                    keyType === Keyword.FUNCTION ||
                    keyType === Keyword.METHOD
                ) {
                    output += this.#compileSubroutine(tok);
                    continue;
                }
            }

            break;
        }

        output += this.#compileSymbol(tok);

        output += '</class>\n';
        return output;
    }

    #compileClassVarDec(tok) {
        let out = '<classVarDec>\n';
        out += this.#compileKeyword(tok);

        tok.advance();
        let tokenType = tok.tokenType();

        // compile the type of the variable
        if (tokenType === TokenType.KEYWORD) {
            const keyType = tok.keywordType();

            if (
                keyType === Keyword.INT ||
                keyType === Keyword.CHAR ||
                keyType === Keyword.BOOLEAN
            ) {
                out += this.#compileKeyword(tok);
            } else {
                throw new Error(`Invalid keyword: ${keyType.description}`);
            }
        } else if (tokenType === TokenType.IDENTIFIER) {
            out += this.#compileIdentifier(tok);
        } else {
            throw new Error(
                `Invalid class declaration: ${tokenType.description}`
            );
        }

        // compile the variable name
        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.IDENTIFIER) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }

        out += this.#compileIdentifier(tok);

        // compile any other variables declared of the same type
        while (true) {
            tok.advance();
            tokenType = tok.tokenType();

            if (tokenType !== TokenType.SYMBOL) {
                throw new Error(`Invalid token: ${tokenType.description}`);
            }

            const currentSymbol = tok.symbol();

            if (currentSymbol === ',') {
                out += this.#compileSymbol(tok);

                // compile the next variable name
                tok.advance();
                tokenType = tok.tokenType();

                if (tokenType !== TokenType.IDENTIFIER) {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }

                out += this.#compileIdentifier(tok);
                continue;
            }
            break;
        }

        // compile the closing semicolon
        out += this.#compileSymbol(tok);

        out += '</classVarDec>\n';

        return out;
    }

    #compileSubroutine(tok) {
        let out = '<subroutineDec>\n';
        out += this.#compileKeyword(tok);

        // compile return type or constructor
        tok.advance();
        let tokenType = tok.tokenType();

        if (tokenType === TokenType.KEYWORD) {
            const keyType = tok.keywordType();

            if (
                keyType === Keyword.VOID ||
                keyType === Keyword.CONSTRUCTOR ||
                keyType === Keyword.INT ||
                keyType === Keyword.CHAR ||
                keyType === Keyword.BOOLEAN
            ) {
                out += this.#compileKeyword(tok);
            } else {
                throw new Error(`Invalid keyword: ${keyType.description}`);
            }
        } else if (tokenType === TokenType.IDENTIFIER) {
            out += this.#compileIdentifier(tok);
        } else {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }

        // compile subroutine name
        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.IDENTIFIER) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileIdentifier(tok);

        // opening paren
        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        // compile list of 0 or more parameters
        out += this.#compileParameterList(tok);

        // closing paren
        out += this.#compileSymbol(tok);

        out += this.#compileSubroutineBody(tok);

        out += '</subroutineDec>\n';

        return out;
    }

    #compileParameterList(tok) {
        let out = '<parameterList>\n';

        tok.advance();
        let tokenType = tok.tokenType();

        if (
            tokenType === TokenType.KEYWORD ||
            tokenType === TokenType.IDENTIFIER
        ) {
            // parameters are present, compile them
            while (true) {
                // compile param type
                if (tokenType === TokenType.KEYWORD) {
                    const keyType = tok.keywordType();

                    if (
                        keyType === Keyword.INT ||
                        keyType === Keyword.CHAR ||
                        keyType === Keyword.BOOLEAN
                    ) {
                        out += this.#compileKeyword(tok);
                    } else {
                        throw new Error(
                            `Invalid keyword: ${keyType.description}`
                        );
                    }
                } else if (tokenType === TokenType.IDENTIFIER) {
                    out += this.#compileIdentifier(tok);
                } else {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }

                // compile param name
                tok.advance();
                tokenType = tok.tokenType();

                if (tokenType !== TokenType.IDENTIFIER) {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }
                out += this.#compileIdentifier(tok);

                // get next param or end of params
                tok.advance();
                tokenType = tok.tokenType();

                if (tokenType === TokenType.SYMBOL) {
                    const symbol = tok.symbol();

                    if (symbol === ',') {
                        out += this.#compileSymbol(tok);

                        // there are more params, continue to get the next one
                        tok.advance();
                        tokenType = tok.tokenType();
                        continue;
                    }
                    break;
                } else {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }
            }
        }

        out += '</parameterList>\n';

        return out;
    }

    #compileSubroutineBody(tok) {
        let out = '<subroutineBody>\n';

        tok.advance();
        let tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }

        // compile opening brace
        out += this.#compileSymbol(tok);

        // compile any var declarations
        while (true) {
            tok.advance(true);
            tokenType = tok.tokenType();

            if (tokenType === TokenType.KEYWORD) {
                const keyType = tok.keywordType();

                if (keyType === Keyword.VAR) {
                    tok.advance();
                    out += this.#compileVarDec(tok);
                    continue;
                }
            }
            break;
        }

        out += this.#compileStatements(tok, true);

        out += this.#compileSymbol(tok);

        out += '</subroutineBody>\n';

        return out;
    }

    #compileVarDec(tok) {
        let out = '<varDec>\n';
        out += this.#compileKeyword(tok);

        tok.advance();
        let tokenType = tok.tokenType();

        // compile the type of the variable
        if (tokenType === TokenType.KEYWORD) {
            const keyType = tok.keywordType();

            if (
                keyType === Keyword.INT ||
                keyType === Keyword.CHAR ||
                keyType === Keyword.BOOLEAN
            ) {
                out += this.#compileKeyword(tok);
            } else {
                throw new Error(`Invalid keyword: ${keyType.description}`);
            }
        } else if (tokenType === TokenType.IDENTIFIER) {
            out += this.#compileIdentifier(tok);
        } else {
            throw new Error(
                `Invalid var declaration: ${tokenType.description}`
            );
        }

        // compile the variable name
        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.IDENTIFIER) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }

        out += this.#compileIdentifier(tok);

        // compile any other variables declared of the same type
        while (true) {
            tok.advance();
            tokenType = tok.tokenType();

            if (tokenType !== TokenType.SYMBOL) {
                throw new Error(`Invalid token: ${tokenType.description}`);
            }

            const currentSymbol = tok.symbol();

            if (currentSymbol === ',') {
                out += this.#compileSymbol(tok);

                // compile the next variable name
                tok.advance();
                tokenType = tok.tokenType();

                if (tokenType !== TokenType.IDENTIFIER) {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }

                out += this.#compileIdentifier(tok);
                continue;
            }
            break;
        }

        // compile the closing semicolon
        out += this.#compileSymbol(tok);

        out += '</varDec>\n';

        return out;
    }

    #compileStatements(tok, read = true) {
        let out = '<statements>\n';
        let readNext = read;

        while (true) {
            if (readNext) {
                tok.advance();
            }

            let tokenType = tok.tokenType();

            if (tokenType !== TokenType.KEYWORD) {
                break;
            }

            const keywordType = tok.keywordType();

            switch (keywordType) {
                case Keyword.LET:
                    out += this.#compileLet(tok);
                    readNext = true;
                    break;
                case Keyword.IF:
                    const ifVal = this.#compileIf(tok);
                    out += ifVal.output;
                    readNext = !ifVal.advanced;
                    break;
                case Keyword.WHILE:
                    out += this.#compileWhile(tok);
                    readNext = true;
                    break;
                case Keyword.DO:
                    out += this.#compileDo(tok);
                    readNext = true;
                    break;
                case Keyword.RETURN:
                    out += this.#compileReturn(tok);
                    readNext = true;
                    break;
                default:
                    throw new Error(
                        `Invalid keyword: ${keywordType.description}`
                    );
            }
        }

        out += '</statements>\n';

        return out;
    }

    #compileLet(tok) {
        let out = '<letStatement>\n';

        out += this.#compileKeyword(tok);

        tok.advance();
        let tokenType = tok.tokenType();

        if (tokenType !== TokenType.IDENTIFIER) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }

        out += this.#compileIdentifier(tok);

        // check for array syntax
        tok.advance(true);
        tokenType = tok.tokenType();

        if (tokenType === TokenType.SYMBOL) {
            const sym = tok.symbol();

            if (sym === '[') {
                tok.advance();
                out += this.#compileSymbol(tok);
                out += this.#compileExpression(tok);

                // compile closing "]"
                tok.advance();
                tokenType = tok.tokenType();

                if (tokenType !== TokenType.SYMBOL) {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }
                out += this.#compileSymbol(tok);
            }
        }

        // compile '=' sign
        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        out += this.#compileExpression(tok);

        // compile semicolon
        tok.advance();
        out += this.#compileSymbol(tok);

        out += '</letStatement>\n';

        return out;
    }

    #compileIf(tok) {
        let out = '<ifStatement>\n';

        out += this.#compileKeyword(tok);

        // compile opening paren
        tok.advance();
        let tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        // compile the expression inside the parens
        out += this.#compileExpression(tok);

        // compile closing paren
        tok.advance();
        out += this.#compileSymbol(tok);

        // compile opening brace
        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        tok.advance(true);
        tokenType = tok.tokenType();

        if (tokenType === TokenType.SYMBOL) {
            // no statements (an empty if)
            out += this.#compileStatements(tok, false);
            tok.advance();
        } else {
            // compile the statements inside the if
            out += this.#compileStatements(tok);
        }

        // compile closing brace
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            console.log(tok.keyword());
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        // compile optional "else" if it's there
        tok.advance();
        tokenType = tok.tokenType();
        let advanced = true;

        if (tokenType === TokenType.KEYWORD) {
            const keyType = tok.keywordType();

            if (keyType === Keyword.ELSE) {
                advanced = false;
                out += this.#compileKeyword(tok);

                // compile opening brace
                tok.advance();
                tokenType = tok.tokenType();

                if (tokenType !== TokenType.SYMBOL) {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }
                out += this.#compileSymbol(tok);

                tok.advance(true);
                tokenType = tok.tokenType();

                if (tokenType === TokenType.SYMBOL) {
                    // no statements (an empty else)
                    out += this.#compileStatements(tok, false);
                    tok.advance();
                } else {
                    // compile the statements inside the else
                    out += this.#compileStatements(tok);
                }

                // compile closing brace
                tokenType = tok.tokenType();

                if (tokenType !== TokenType.SYMBOL) {
                    throw new Error(`Invalid token: ${tokenType.description}`);
                }
                out += this.#compileSymbol(tok);
            }
        }

        out += '</ifStatement>\n';

        return {
            output: out,
            advanced: advanced,
        };
    }

    #compileWhile(tok) {
        let out = '<whileStatement>\n';

        out += this.#compileKeyword(tok);

        // compile opening paren
        tok.advance();
        let tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        // compile the expression inside the parens
        out += this.#compileExpression(tok);

        // compile closing paren
        tok.advance();
        out += this.#compileSymbol(tok);

        // compile opening brace
        tok.advance();
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        tok.advance(true);
        tokenType = tok.tokenType();

        if (tokenType === TokenType.SYMBOL) {
            // no statements (an empty while)
            out += this.#compileStatements(tok, false);
            tok.advance();
        } else {
            // compile the statements inside the while
            out += this.#compileStatements(tok);
        }

        // compile closing brace
        tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        out += '</whileStatement>\n';

        return out;
    }

    #compileDo(tok) {
        let out = '<doStatement>\n';
        let tokenType = null;

        // compile do keyword
        out += this.#compileKeyword(tok);

        // compile subroutine name
        tok.advance();
        const ident = this.#compileIdentifier(tok);
        out += this.#compileSubroutineCall(tok, ident);

        // compile semicolon
        tok.advance();
        tokenType = tok.tokenType();
        if (tokenType !== TokenType.SYMBOL) {
            throw new Error(`Invalid token: ${tokenType.description}`);
        }
        out += this.#compileSymbol(tok);

        out += '</doStatement>\n';

        return out;
    }

    #compileReturn(tok) {
        let out = '<returnStatement>\n';

        out += this.#compileKeyword(tok);

        // check if there is an expression
        tok.advance(true);
        let tokenType = tok.tokenType();

        if (tokenType !== TokenType.SYMBOL) {
            out += this.#compileExpression(tok);
        }

        // compile semicolon
        tok.advance();
        out += this.#compileSymbol(tok);

        out += '</returnStatement>\n';

        return out;
    }

    #compileExpression(tok) {
        let out = '<expression>\n';

        out += this.#compileTerm(tok);

        // check for an "op" and then another term
        while (true) {
            tok.advance(true);
            let tokenType = tok.tokenType();

            if (tokenType === TokenType.SYMBOL) {
                const sym = tok.symbol();

                if (
                    sym === '+' ||
                    sym === '-' ||
                    sym === '*' ||
                    sym === '/' ||
                    sym === '&' ||
                    sym === '|' ||
                    sym === '<' ||
                    sym === '>' ||
                    sym === '='
                ) {
                    tok.advance();
                    out += this.#compileSymbol(tok);
                    out += this.#compileTerm(tok);
                    continue;
                }
                break;
            }
            break;
        }

        out += '</expression>\n';

        return out;
    }

    #compileTerm(tok) {
        let out = '<term>\n';

        tok.advance();
        let tokenType = tok.tokenType();

        switch (tokenType) {
            case TokenType.IDENTIFIER:
                const ident = this.#compileIdentifier(tok);

                tok.advance(true);
                tokenType = tok.tokenType();

                if (tokenType === TokenType.SYMBOL) {
                    const symb = tok.symbol();

                    if (symb === '(' || symb === '.') {
                        // assume it's a subroutine call
                        out += this.#compileSubroutineCall(tok, ident);
                    } else if (symb === '[') {
                        // array access varName[exp]
                        out += ident;

                        tok.advance();
                        out += this.#compileSymbol(tok);
                        out += this.#compileExpression(tok);

                        // compile closing "]"
                        tok.advance();
                        tokenType = tok.tokenType();

                        if (tokenType !== TokenType.SYMBOL) {
                            throw new Error(
                                `Invalid token: ${tokenType.description}`
                            );
                        }
                        out += this.#compileSymbol(tok);
                    } else {
                        out += ident;
                    }
                }
                break;
            case TokenType.INT:
                out += this.#compileIntegerConstant(tok);
                break;
            case TokenType.KEYWORD:
                out += this.#compileKeyword(tok);
                break;
            case TokenType.STRING:
                out += this.#compileStringConstant(tok);
                break;
            case TokenType.SYMBOL:
                // this is a "(expression)" or an "(unaryOp term)"
                const sym = tok.symbol();

                if (sym === '(') {
                    out += this.#compileSymbol(tok);

                    out += this.#compileExpression(tok);

                    // compile closing paren of the expression
                    tok.advance();
                    tokenType = tok.tokenType();

                    if (tokenType !== TokenType.SYMBOL) {
                        throw new Error(
                            `Invalid token: ${tokenType.description}`
                        );
                    }
                    out += this.#compileSymbol(tok);
                } else if (sym === '~' || sym === '-') {
                    // compile unary operation
                    out += this.#compileSymbol(tok);
                    out += this.#compileTerm(tok);
                } else {
                    throw new Error(`Invalid symbol: ${sym}`);
                }
                break;
            default:
                throw new Error(`Invalid token: ${tokenType.description}`);
        }

        out += '</term>\n';

        return out;
    }

    #compileSubroutineCall(tok, ident) {
        let out = ident;
        let tokenType = null;

        tok.advance();
        const symb = tok.symbol();
        out += this.#compileSymbol(tok);

        if (symb === '(') {
            // calling a regular function
            out += this.#compileExpressionList(tok);

            tok.advance();
            tokenType = tok.tokenType();

            // compile closing paren
            if (tokenType !== TokenType.SYMBOL) {
                throw new Error(`Invalid token: ${tokenType.description}`);
            }
            out += this.#compileSymbol(tok);
        } else if (symb === '.') {
            // calling a method
            tok.advance();
            tokenType = tok.tokenType();

            // compile the name of the method
            if (tokenType !== TokenType.IDENTIFIER) {
                throw new Error(`Invalid token: ${tokenType.description}`);
            }
            out += this.#compileIdentifier(tok);

            // compile opening paren
            tok.advance();
            tokenType = tok.tokenType();

            if (tokenType !== TokenType.SYMBOL) {
                throw new Error(`Invalid token: ${tokenType.description}`);
            }
            out += this.#compileSymbol(tok);

            // compile expression list
            out += this.#compileExpressionList(tok);

            tok.advance();
            tokenType = tok.tokenType();

            // compile closing paren
            if (tokenType !== TokenType.SYMBOL) {
                throw new Error(`Invalid token: ${tokenType.description}`);
            }
            out += this.#compileSymbol(tok);
        } else {
            throw new Error(`Invalid symbol: ${symb}`);
        }

        return out;
    }

    #compileExpressionList(tok) {
        let out = '<expressionList>\n';
        let tokenType = null;

        // get initial expression (if any)
        tok.advance(true);
        tokenType = tok.tokenType();

        // expressions are not present inside the expression list
        if (tokenType === TokenType.SYMBOL) {
            const symb = tok.symbol();

            if (symb == ')') {
                // tok.advance();
                // tokenType = tok.tokenType();

                // out += this.#compileSymbol(tok);
                out += '</expressionList>\n';

                return out;
            }
        }

        out += this.#compileExpression(tok);

        while (true) {
            // get the next expression (if any)
            tok.advance(true);
            tokenType = tok.tokenType();

            if (tokenType === TokenType.SYMBOL) {
                const symb = tok.symbol();
                if (symb === ',') {
                    tok.advance();
                    out += this.#compileSymbol(tok);
                    out += this.#compileExpression(tok);
                    continue;
                }
                break;
            }
            break;
        }

        out += '</expressionList>\n';

        return out;
    }

    async #tokenizeFile(filePath) {
        const tokenizer = new Tokenizer(filePath);
        await tokenizer.init();

        let tokenizedString = '<tokens>\n';

        while (true) {
            if (!tokenizer.hasMoreTokens()) {
                break;
            }

            tokenizer.advance();
            const tokenType = tokenizer.tokenType();

            switch (tokenType) {
                case TokenType.IDENTIFIER:
                    tokenizedString += this.#compileIdentifier(tokenizer);
                    break;
                case TokenType.INT:
                    tokenizedString += this.#compileIntegerConstant(tokenizer);
                    break;
                case TokenType.KEYWORD:
                    tokenizedString += this.#compileKeyword(tokenizer);
                    break;
                case TokenType.STRING:
                    tokenizedString += this.#compileStringConstant(tokenizer);
                    break;
                case TokenType.SYMBOL:
                    tokenizedString += this.#compileSymbol(tokenizer);
                    break;
                default:
                    throw new Error(`Invalid token type: ${tokenType}`);
            }
        }
        tokenizedString += '</tokens>\n';

        // save the XML file with the tokens
        const fileElements = path.parse(filePath);
        const tokenizedFilePath =
            fileElements.dir + '/' + fileElements.name + 'T.xml';

        try {
            const handle = await fs.open(tokenizedFilePath, 'w+');
            await fs.writeFile(handle, tokenizedString);
            handle.close();
        } catch (e) {
            throw new Error(`${e.message}`);
        }
    }

    #compileIdentifier(tok) {
        let out = '<identifier> ';
        out += tok.identifier();
        out += ' </identifier>\n';

        return out;
    }

    #compileIntegerConstant(tok) {
        let out = '<integerConstant> ';
        out += tok.intVal();
        out += ' </integerConstant>\n';

        return out;
    }

    #compileKeyword(tok) {
        let out = '<keyword> ';
        out += tok.keyword();
        out += ' </keyword>\n';

        return out;
    }

    #compileStringConstant(tok) {
        let out = '<stringConstant> ';
        out += tok.stringVal();
        out += ' </stringConstant>\n';

        return out;
    }

    #compileSymbol(tok) {
        let out = '<symbol> ';
        out += tok.symbol(true);
        out += ' </symbol>\n';

        return out;
    }
}
