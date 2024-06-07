(include "compiler.scm")

; a: our spread-arguments code generator
(define (spread-arguments operands)
  (if (= (length operands) 2)     
    (preserving '(env)
                (compile (car operands) 'arg1 'next)
                (preserving '(arg1)
                            (compile (cadr operands) 'arg2 'next)
                            (make-instruction-sequence
                              '(arg1) '() '())))
    (error "Wrong number of arguments to spread-arguments -- COMPILE" operands)))

; b: code generators for + - * and = and changes on "compile" for the dispatch
; d: compile-sum and compile-mul support an arbitrary number of arguments
(define (sum? exp) (tagged-list? exp '+))
(define (mul? exp) (tagged-list? exp '*))
(define (minus? exp) (tagged-list? exp '-))
(define (is-equal? exp) (tagged-list? exp '=))
(define all-regs '(env proc val argl arg1 arg2 continue))

(define (compile-sum exp target linkage)
  (compile-open-coded '+ (operands exp) target linkage))

(define (compile-mul exp target linkage)
  (compile-open-coded '* (operands exp) target linkage))

(define (compile-minus exp target linkage)
  (compile-open-coded-simple '- (operands exp) target linkage))

(define (compile-equal exp target linkage)
  (compile-open-coded-simple '= (operands exp) target linkage))

(define (compile-open-coded-simple operator operands target linkage)
  (end-with-linkage
    linkage
    (append-instruction-sequences
      (spread-arguments operands)
      (make-instruction-sequence
        '(arg1 arg2)
        `(,target)
        `((assign ,target (op ,operator) (reg arg1) (reg arg2)))))))

(define (compile-open-coded operator operands target linkage)
  (let ((ops (length operands)))
    (cond
      ((= ops 0) (compile '0 target linkage))
      ((= ops 1) (compile (car operands) target linkage))
      (else
        (end-with-linkage
          linkage
          (preserving
            '(env)
            (compile (car operands) 'arg1 'next)
            (compile-open-coded-rest operator (cdr operands) target)))))))

(define (compile-open-coded-rest operator operands target)
  (let ((last-operand? (null? (cdr operands))))
    (let ((targ (if last-operand?
                  target
                  'arg1)))
      (let ((instructions
              (preserving '(arg1)
                          (compile (car operands) 'arg2 'next)
                          (make-instruction-sequence
                            '(arg1 arg2)
                            `(,targ)
                            `((assign ,targ (op ,operator)
                                      (reg arg1) (reg arg2)))))))
        (if last-operand?
          instructions
          (preserving
            '(env)
            instructions
            (compile-open-coded-rest operator (cdr operands) target)))))))

(define (compile exp target linkage)
  (cond ((self-evaluating? exp)
         (compile-self-evaluating exp target linkage))
        ((quoted? exp) (compile-quoted exp target linkage))
        ((variable? exp)
         (compile-variable exp target linkage))
        ((assignment? exp)
         (compile-assignment exp target linkage))
        ((definition? exp)
         (compile-definition exp target linkage))
        ((if? exp) (compile-if exp target linkage))
        ((lambda? exp) (compile-lambda exp target linkage))
        ((begin? exp)
         (compile-sequence (begin-actions exp)
                           target
                           linkage))
        ((cond? exp) (compile (cond->if exp) target linkage))
        ((sum? exp) (compile-sum exp target linkage))
        ((minus? exp) (compile-minus exp target linkage))
        ((is-equal? exp) (compile-equal exp target linkage))
        ((mul? exp) (compile-mul exp target linkage))
        ((application? exp)
         (compile-application exp target linkage))
        (else
         (error "Unknown expression type -- COMPILE" exp))))

; c: compile the factorial procedure for testing
(define prog '(define (factorial n)
                (if (= n 1)
                  1
                  (* n (factorial (- n 1))))))

(define code (compile prog 'val 'next))
(pretty-print code)
(newline)
