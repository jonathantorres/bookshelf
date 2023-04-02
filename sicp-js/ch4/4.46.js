// this program must be run from the Source environment
// using the Non-deterministic variant
// https://sourceacademy.org/playground
const nouns = list("noun", "student", "professor", "cat", "class");
const verbs = list("verb", "studies", "lectures", "eats", "sleeps");
const articles = list("article", "the", "a");
const prepositions = list("prep", "for", "to", "in", "by", "with");
const adjectives = list("adjective", "blue", "ugly", "cute", "black", "pretty");
const adverbs = list("adverb", "hastily", "quickly", "slowly");
let not_yet_parsed = null;

function parse_word(word_list) {
    require(! is_null(not_yet_parsed));
    require(! is_null(member(head(not_yet_parsed), tail(word_list))));
    const found_word = head(not_yet_parsed);
    not_yet_parsed = tail(not_yet_parsed);
    return list(head(word_list), found_word);
}

function parse_simple_verb() {
    return amb(
        list("simple-verb", parse_word(adverbs), parse_word(verbs)),
        parse_word(verbs)
    );
}

function parse_simple_noun_phrase() {
    const art = parse_word(articles);
    const tag = "simple-noun-phrase";

    return amb(
        list(tag, art, parse_word(adjectives), parse_word(nouns)),
        list(tag, art, parse_word(nouns))
    );
}

function parse_prepositional_phrase() {
    return list("prep-phrase",
                parse_word(prepositions),
                parse_noun_phrase());
}

function parse_noun_phrase() {
    function maybe_extend(noun_phrase) {
        return amb(noun_phrase,
                   maybe_extend(list("noun-phrase",
                                     noun_phrase,
                                     parse_prepositional_phrase())));
    }
    return maybe_extend(parse_simple_noun_phrase());
}

function parse_verb_phrase() {
    function maybe_extend(verb_phrase) {
        return amb(verb_phrase,
                   maybe_extend(list("verb-phrase",
                                     verb_phrase,
                                     parse_prepositional_phrase())));
    }
    return maybe_extend(parse_simple_verb());
}

function parse_sentence() {
    return list("sentence",
                parse_noun_phrase(),
                parse_verb_phrase());
}

function parse_input(input) {
    not_yet_parsed = input;
    const sent = parse_sentence();
    require(is_null(not_yet_parsed));
    return sent;
}

display_list(parse_input(
    list("the", "professor", "lectures", "to", "the", "blue",
         "student", "in", "the", "class", "with", "the", "cat")
));

