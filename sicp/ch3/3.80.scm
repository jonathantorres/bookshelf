(include "streams.scm")

(define (integral delayed-integrand initial-value dt)
  (cons-stream initial-value
               (let ((integrand (force delayed-integrand)))
                 (if (stream-null? integrand)
                   the-empty-stream
                   (integral (delay (stream-cdr integrand))
                             (+ (* dt (stream-car integrand))
                                initial-value)
                             dt)))))

(define (RLC R L C dt)
  (lambda (vc0 il0)
    (define vc (integral (delay dvc) vc0 dt))
    (define il (integral (delay dil) il0 dt))
    (define dvc (scale-stream il (- (/ 1 C))))
    (define dil (add-streams
                  (scale-stream vc (/ 1 L))
                  (scale-stream il (- (/ R L)))))
    (stream-map cons vc il)))

(define RLC1 (RLC 5 1 1 0.5))

(display (stream-ref (RLC1 1 2) 10)) (newline)
