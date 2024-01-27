(include "streams.scm")

(define (make-zero-crossings input-stream last-value last-avpt)
  (let ((avpt (/ (+ (stream-car input-stream) last-value) 2)))
    (cons-stream (sign-change-detector avpt last-avpt)
                 (make-zero-crossings (stream-cdr input-stream)
                                      (stream-car input-stream)
                                      avpt))))

(define (sign-change-detector a b)
  (cond ((and (< b 0) (< 0 a)) 1)
        ((and (< a 0) (< 0 b)) -1)
        (else 0)))

(define ones (cons-stream 1 ones))
(define integers (cons-stream 1 (add-streams ones integers)))
(define sense-data integers)

(define zero-crossings (make-zero-crossings sense-data 1 2))

(display-stream zero-crossings)
