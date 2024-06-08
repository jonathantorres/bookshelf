(include "compiler-env.scm")

(define (spread-arguments operands env)
  (if (= (length operands) 2)     
    (preserving '(env)
                (compile (car operands) 'arg1 'next env)
                (preserving '(arg1)
                            (compile (cadr operands) 'arg2 'next env)
                            (make-instruction-sequence
                              '(arg1) '() '())))
    (error "Wrong number of arguments to spread-arguments -- COMPILE" operands)))

(define (sum? exp) (tagged-list? exp '+))
(define (mul? exp) (tagged-list? exp '*))
(define (minus? exp) (tagged-list? exp '-))
(define (is-equal? exp) (tagged-list? exp '=))
(define all-regs '(env proc val argl arg1 arg2 continue))

(define (compile-sum exp target linkage env)
  (compile-open-coded '+ (operands exp) target linkage env))

(define (compile-mul exp target linkage env)
  (compile-open-coded '* (operands exp) target linkage env))

(define (compile-minus exp target linkage env)
  (compile-open-coded-simple '- (operands exp) target linkage env))

(define (compile-equal exp target linkage env)
  (compile-open-coded-simple '= (operands exp) target linkage env))

(define (compile-open-coded-simple operator operands target linkage env)
  (end-with-linkage
    linkage
    (append-instruction-sequences
      (spread-arguments operands env)
      (make-instruction-sequence
        '(arg1 arg2)
        `(,target)
        `((assign ,target (op ,operator) (reg arg1) (reg arg2)))))))

(define (compile-open-coded operator operands target linkage env)
  (let ((ops (length operands)))
    (cond
      ((= ops 0) (compile '0 target linkage env))
      ((= ops 1) (compile (car operands) target linkage env))
      (else
        (end-with-linkage
          linkage
          (preserving
            '(env)
            (compile (car operands) 'arg1 'next env)
            (compile-open-coded-rest operator (cdr operands) target env)))))))

(define (compile-open-coded-rest operator operands target env)
  (let ((last-operand? (null? (cdr operands))))
    (let ((targ (if last-operand?
                  target
                  'arg1)))
      (let ((instructions
              (preserving '(arg1)
                          (compile (car operands) 'arg2 'next env)
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
            (compile-open-coded-rest operator (cdr operands) target env)))))))

(define (compile exp target linkage env)
  (cond ((self-evaluating? exp)
         (compile-self-evaluating exp target linkage))
        ((quoted? exp) (compile-quoted exp target linkage))
        ((variable? exp)
         (compile-variable exp target linkage env))
        ((assignment? exp)
         (compile-assignment exp target linkage env))
        ((definition? exp)
         (compile-definition exp target linkage env))
        ((if? exp) (compile-if exp target linkage env))
        ((lambda? exp) (compile-lambda exp target linkage env))
        ((begin? exp)
         (compile-sequence (begin-actions exp)
                           target
                           linkage
                           env))
        ((cond? exp) (compile (cond->if exp) target linkage env))
        ((sum? exp) (compile-sum exp target linkage env))
        ((minus? exp) (compile-minus exp target linkage env))
        ((is-equal? exp) (compile-equal exp target linkage env))
        ((mul? exp) (compile-mul exp target linkage env))
        ((application? exp)
         (compile-application exp target linkage env))
        (else
         (error "Unknown expression type -- COMPILE" exp))))

; compile the factorial procedure for testing
(define prog '(define (factorial n)
                (if (= n 1)
                  1
                  (* n (factorial (- n 1))))))

(define code (compile prog 'val 'next '()))
(pretty-print code)
(newline)
