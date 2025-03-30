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
        const tree = await this.#compileFile(filePath, true);

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

        // TODO: use compiler engine to create the parse tree FOR REAL!
        const tree = 'nothing here yet :(';

        return tree;
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
                    tokenizedString += '<identifier> ';
                    tokenizedString += tokenizer.identifier();
                    tokenizedString += ' </identifier>\n';
                    break;
                case TokenType.INT:
                    tokenizedString += '<integerConstant> ';
                    tokenizedString += tokenizer.intVal();
                    tokenizedString += ' </integerConstant>\n';
                    break;
                case TokenType.KEYWORD:
                    tokenizedString += '<keyword> ';
                    tokenizedString += tokenizer.keyword();
                    tokenizedString += ' </keyword>\n';
                    break;
                case TokenType.STRING:
                    tokenizedString += '<stringConstant> ';
                    tokenizedString += tokenizer.stringVal();
                    tokenizedString += ' </stringConstant>\n';
                    break;
                case TokenType.SYMBOL:
                    tokenizedString += '<symbol> ';
                    tokenizedString += tokenizer.symbol(true);
                    tokenizedString += ' </symbol>\n';
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
}
