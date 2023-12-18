; A situation in which coercion won't work as expected is if we have 3 types: A, B and C
; and we have the following coercion operations: A->B and C->B
; if we evaluate a procedure call for (A B C) will attempt to coerce (A B C) and (B B B)
; and fail, while we can coerce C to B and attempt the same operation successfully

; try to coerce all of the arguments to a common type
(define (coerce-types args)
  ; coerce a list of types to a specific type
  (define (coerce-to type types)
    (if (null? types)
      '()
      (let ((type1 (type-tag type))
            (type2 (type-tag (car types)))
            (a1 type)
            (a2 (car types)))
        (let ((t1->t2 (get-coercion type1 type2))
              (t2->t1 (get-coercion type2 type1)))
          (cond (t1->t2
                  (cons (t1->t2 a1) (coerce-to type (cdr types))))
                (t2->t1
                  (cons (t2->t1 a2) (coerce-to type (cdr types))))
                (else
                  #f))))))

  ; recursively try to coerce all arguments to the first argument,
  ; otherwise try the second argument and so on
  (define (coerce-types-rec types)
    (if (null? types)
      #f
      (let ((coerced-types (coerce-to (car types) args)))
        (if (= #f coerced-types)
          (coerce-types-rec (cdr types))
          coerce-types))))

  (coerce-types-rec args))

; use apply-generic to try to coerce all arguments to the type of the first argument
; if that fails, then try with the second argument, and so on
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
          (apply proc (map contents args))
          (let ((new-args (coerce-types args)))
            (if (= new-args #f)
              (error "No method for these types" (list op type-tags))
              (apply-generic op new-args)))))))

