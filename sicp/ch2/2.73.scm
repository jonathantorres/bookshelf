;; table operations
(define (assoc key records)
  (cond ((null? records) #f)
        ((equal? key (caar records)) (car records))
        (else (assoc key (cdr records)))))

(define (make-table)
  (let ((local-table (list '*table*)))
    (define (lookup key-1 key-2)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (cdr record)
                  #f))
            #f)))
    (define (insert! key-1 key-2 value)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (set-cdr! record value)
                  (set-cdr! subtable
                            (cons (cons key-2 value)
                                  (cdr subtable)))))
            (set-cdr! local-table
                      (cons (list key-1
                                  (cons key-2 value))
                            (cdr local-table)))))
      'ok)
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unknown operation -- TABLE" m))))
    dispatch))

(define operation-table (make-table))
(define get (operation-table 'lookup-proc))
(define put (operation-table 'insert-proc!))

;; a: The deriv program was changed to a data-directed style approach.
;;    The operator symbols (+ *) are used as a key to the table to find the
;;    appropriate operation. The predicates cannot be used since they only
;;    operate on the expression and not on a variable, in other words, they are not tagged

;; changes on symbolic differentiation program
(define (operator exp) (car exp))
(define (operands exp) (cdr exp))
(define (variable? x) (symbol? x))
(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

;; b: installing the deriv package and it's procedures
(define (install-deriv-package)
  ;; internal procedures
  (define (make-sum a1 a2)
    (cond ((=number? a1 0) a2)
          ((=number? a2 0) a1)
          ((and (number? a1) (number? a2)) (+ a1 a2))
          (else (list '+ a1 a2))))

  (define (make-product m1 m2)
    (cond ((or (=number? m1 0) (=number? m2 0)) 0)
          ((=number? m1 1) m2)
          ((=number? m2 1) m1)
          ((and (number? m1) (number? m2)) (* m1 m2))
          (else
            (list '* m1 m2))))

  (define (addend s) (car s))
  (define (augend s) (cadr s))

  (define (multiplier p) (car p))
  (define (multiplicand p) (cadr p))

  ;; c: exponentiation rule, it's installed on the call to (put) below
  (define (make-exponentiation base exp)
    (cond ((=number? exp 0) 1)
          ((=number? exp 1) base)
          ((=number? base 1) 1)
          ((and (number? base) (number? exp)) (expt base exp))
          (else
            (list '** base exp))))

  (define (base e) (car e))
  (define (exponent e) (cadr e))

  (define (=number? exp num)
    (and (number? exp) (= exp num)))

  (put 'deriv '+ (lambda (exp var)
                   (make-sum (deriv (addend exp) var)
                             (deriv (augend exp) var))))

  (put 'deriv '* (lambda (exp var)
                   (make-sum
                     (make-product (multiplier exp)
                                   (deriv (multiplicand exp) var))
                     (make-product (deriv (multiplier exp) var)
                                   (multiplicand exp)))))

  (put 'deriv '** (lambda (exp var)
                    (make-product
                      (make-product (exponent exp)
                                    (make-exponentiation (base exp)
                                                         (- (exponent exp) 1)))
                      (deriv (base exp) var))))
  'done)

(install-deriv-package)


;; d: No changes are needed on the derivative system. The only changes
;;    that must be made are on the calls to (put) to install them in the correct order
(define (deriv exp var)
  (cond ((number? exp) 0)
        ((variable? exp) (if (same-variable? exp var) 1 0))
        (else
          ((get 'deriv (operator exp)) (operands exp) var))))

(display (deriv '(+ x 3) 'x)) (newline)
(display (deriv '(* x y) 'x)) (newline)
(display (deriv '(* (* x y) (+ x 3)) 'x)) (newline)
(display (deriv '(** x 20) 'x)) (newline)
