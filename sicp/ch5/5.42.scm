(include "compiler-env.scm")

; procedures from 5.39 and 5.41
(define (address-frame address)
  (car address))

(define (address-offset address)
  (cdr address))

(define (lexical-address frame offset)
  (cons frame offset))

(define (find-variable var env)
  (define (find-var v e n)
    (cond ((null? e) #f)
          ((eq? v (address-frame e)) n)
          (else
            (find-var v (address-offset e) (+ n 1)))))
  (define (find-frame frames frame)
    (if (null? frames)
      'not-found
      (let ((found (find-var var (address-frame frames) 0)))
        (if found
          (lexical-address frame found)
          (find-frame (address-offset frames) (+ frame 1))))))
  (find-frame env 0))

; changes on compile-variable
(define (compile-variable exp target linkage env)
  (let ((address (find-variable exp env)))
    (if (eq? address 'not-found)
      (end-with-linkage linkage
                        (make-instruction-sequence '(env)
                                                   (list target)
                                                   `((assign ,target
                                                             (op lookup-variable-value)
                                                             (const ,exp)
                                                             (reg env)))))
      (end-with-linkage linkage
                        (make-instruction-sequence '(env)
                                                   (list target)
                                                   `((assign ,target
                                                             (op lexical-address-lookup)
                                                             (const ,address)
                                                             (reg env))))))))

; changes on compile-assignment
(define (compile-assignment exp target linkage env)
  (let ((var (assignment-variable exp))
        (get-value-code
         (compile (assignment-value exp) 'val 'next env)))
    (let ((address (find-variable exp env)))
      (if (eq? address 'not-found)
        (end-with-linkage linkage
                          (preserving '(env)
                                      get-value-code
                                      (make-instruction-sequence
                                        '(env val) (list target)
                                        `((perform (op set-variable-value!)
                                                   (const ,var)
                                                   (reg val)
                                                   (reg env))
                                          (assign ,target (const ok))))))
        (end-with-linkage linkage
                          (preserving '(env)
                                      get-value-code
                                      (make-instruction-sequence
                                        '(env val) (list target)
                                        `((perform (op lexical-address-set!)
                                                   (const ,address)
                                                   (reg val)
                                                   (reg env))
                                          (assign ,target (const ok))))))))))

; compile the nested lambda
(define prog '(((lambda (x y)
                  (lambda (a b c d e)
                    ((lambda (y z) (* x y z))
                     (* a b x)
                     (+ c d x))))
                3
                4)))

(define code (compile prog 'val 'next '()))
(pretty-print code)
(newline)
