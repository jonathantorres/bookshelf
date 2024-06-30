<?php

$instructions = [];
$translated_instructions = [];

while ($line = fgets(STDIN)) {
    $instructions[] = str_replace("\n", "", $line);
}

$first_label = true;

foreach ($instructions as $i => $instruction) {
    $new_instruction = translate_instruction($instruction, $i);

    if ($new_instruction != '' && !str_contains($new_instruction, '(')) {
        // this is a label
        $label_name = $new_instruction;
        $close_bracket = "}\n\n";

        if ($first_label) {
            $first_label   = false;
            $close_bracket = '';
        } else {
            $prev_inst = $instructions[$i - 1];

            if (!str_starts_with($prev_inst, '(goto')) {
                $goto = 'go_to(label(' . $label_name . '))';
                $close_bracket = $goto . "\n" . $close_bracket;
            }
        }

        $new_instruction = $close_bracket . 'func ' . $label_name . '() {';
    }

    $translated_instructions[] = $new_instruction;
}

echo "package main\n\n";

foreach ($translated_instructions as $i => $inst) {
    if (!empty($inst)) {
        echo $inst . "\n";
    }
}

echo "}";

function translate_instruction($inst, $index = 0) {
    $inst = hyphen_to_underscore($inst);
    $inst = question_to_is($inst);
    $inst = remove_bang($inst);

    if (str_starts_with($inst, '(assign')) {
        // assign instruction
        $inst = translate_assign($inst);
    } else if (str_starts_with($inst, '(op')) {
        // op instruction
        $inst = translate_op($inst);
    } else if (str_starts_with($inst, '(test')) {
        $inst = translate_test($inst, $index);
    } else if (str_starts_with($inst, '(perform')) {
        $inst = translate_perform($inst);
    } else if (str_starts_with($inst, '(save')) {
        // save instruction
        $inst = translate_save($inst);
    } else if (str_starts_with($inst, '(restore')) {
        // restore instruction
        $inst = translate_restore($inst);
    } else if (str_starts_with($inst, '(goto')) {
        // goto instruction
        $inst = translate_goto($inst);
    } else if (str_starts_with($inst, '(label')) {
        // label instruction
        $inst = translate_label($inst);
    } else if (str_starts_with($inst, '(reg')) {
        // reg instruction
        $inst = translate_reg($inst);
    } else if (str_starts_with($inst, '(const')) {
        // const instruction
        $inst = translate_const($inst);
    } else if (str_starts_with($inst, '(branch')) {
        // ignore the branch instruction, since it's handled by the "test" instruction
        return '';
    }

    // this must be a label
    return $inst;
}

function translate_assign($inst) {
    $inst = str_replace('(assign', '', $inst);
    $inst = trim($inst);
    $pieces = explode(' ', $inst);
    $reg = trim($pieces[0]);
    $inst = ltrim($inst, $reg);
    $inst = rtrim($inst, ')');
    $inst = trim($inst);
    $rest = translate_instruction(trim($inst));
    $reg = str_replace('continue', 'cont', $reg);

    return 'assign(' . $reg . ', ' . $rest . ')';
}

function translate_op($inst) {
    $inst = str_replace('(op', '', $inst);
    $inst = trim($inst);
    $pieces = explode(' ', $inst);
    $orig_func_name = str_replace([' ', ')', '('], '', $pieces[0]);
    $func_name = hyphen_to_underscore($orig_func_name);
    $func_name = question_to_is($func_name);
    $func_name = remove_bang($func_name);
    $func_name = trim($func_name);
    $inst = ltrim($inst, $orig_func_name . ')');
    $inst = trim($inst, ')');
    $inst = trim($inst);

    $pieces = explode(') ', $inst);
    $count = count($pieces);
    $rest = '';

    foreach ($pieces as $i => $piece) {
        if (!str_ends_with($piece, ')')) {
            $piece .= ')';
        }

        $rest .= translate_instruction($piece);

        if ($i < $count - 1) {
            $rest .= ', ';
        }
    }

    return $func_name . '(' . $rest . ')';
}

// TODO: this is incomplete
function translate_const($inst) {
    $inst = str_replace('(const', '', $inst);
    $inst = rtrim($inst, ')');

    return 'constant("' . trim($inst) . '")';
}

function translate_reg($inst) {
    $inst = str_replace(['(', ')'], '', $inst);
    $pieces = explode(' ', $inst);
    $reg = $pieces[1];
    $reg = str_replace('continue', 'cont', $reg);

    return $pieces[0] . '(' . $reg . ')';
}

function translate_test($inst, $i) {
    global $instructions;

    $inst = str_replace('(test', '', $inst);
    $inst = trim($inst);
    $inst = rtrim($inst, ')');
    $rest = translate_instruction($inst);
    $branch_inst = $instructions[$i + 1];
    $branch_inst = str_replace(['(', ')'], '', $branch_inst);
    $pieces = explode(' ', $branch_inst);
    $label_name = trim($pieces[2]);
    $label_name = hyphen_to_underscore($label_name);
    $label_name = question_to_is($label_name);
    $label_name = remove_bang($label_name);

    return "if test(" . $rest . ") {\n" . $label_name . "()\nreturn\n}";
}

function translate_perform($inst) {
    $inst = str_replace('(perform', '', $inst);
    $inst = rtrim($inst, ')');
    $inst = trim($inst);

    return translate_op($inst);
}

function translate_label($inst) {
    $inst = str_replace(['(', ')'], '', $inst);
    $pieces = explode(' ', $inst);
    $fun = trim($pieces[1]);

    return 'label(' . $fun . ')';
}

function translate_restore($inst) {
    $inst = str_replace(['(', ')'], '', $inst);
    $pieces = explode(' ', $inst);
    $reg = trim($pieces[1]);
    $reg = str_replace('continue', 'cont', $reg);

    return 'restore(' . $reg . ')';
}

function translate_save($inst) {
    $inst = str_replace(['(', ')'], '', $inst);
    $pieces = explode(' ', $inst);
    $reg = trim($pieces[1]);
    $reg = str_replace('continue', 'cont', $reg);

    return 'save(*' . $reg . ')';
}

function translate_goto($inst) {
    $inst = str_replace(['(', ')'], '', $inst);
    $pieces = explode(' ', $inst);
    $proc = trim($pieces[1]);
    $location = trim($pieces[2]);
    $location = str_replace('continue', 'cont', $location);

    return 'go_to(' . $proc . '(' . $location . '))';
}

function hyphen_to_underscore($inst) {
    return str_replace('-', '_', $inst);
}

function remove_bang($inst) {
    return str_replace('!', '', $inst);
}

function question_to_is($inst) {
    if (str_contains($inst, '?')) {
        $inst = preg_replace('/\w+\?/', "is_$0", $inst);
        return str_replace('?', '', $inst);
    }

    return $inst;
}

?>
