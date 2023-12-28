(define random-init 0)
(define (rand-update x) (+ x 1))
(define rand
  (let ((x random-init))
    (define (dispatch m)
      (cond ((eq? m 'generate)
             (set! x (rand-update x))
             x)
            ((eq? m 'reset)
             (lambda (n)
               (set! x n)))
            (else
              (error "Unknown message -- RAND" m))))
    dispatch))

  (display (rand 'generate)) (newline)
  (display (rand 'generate)) (newline)
  (display (rand 'generate)) (newline)

  ((rand 'reset) 0)
  (display (rand 'generate)) (newline)
