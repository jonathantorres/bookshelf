(include "streams.scm")

(define (smooth s)
  (define (smooth-stream s prev)
    (let ((f (stream-car s))
          (r (stream-cdr s)))
      (cons-stream
        (/ (+ f prev) 2)
        (smooth-stream (stream-cdr s) (stream-car s)))))
  (cons-stream
    (stream-car s)
    (smooth-stream (stream-cdr s) (stream-car s))))

(define (make-zero-crossings input-stream last-value)
  (let ((s (smooth input-stream)))
    (stream-map
      sign-change-detector
      s
      (cons-stream 0 s))))

(define (sign-change-detector a b)
  (cond ((and (< b 0) (< 0 a)) 1)
        ((and (< a 0) (< 0 b)) -1)
        (else 0)))

(define ones (cons-stream 1 ones))
(define integers (cons-stream 1 (add-streams ones integers)))
(define sense-data integers)

(define zero-crossings (make-zero-crossings sense-data 1))

(display-stream zero-crossings)
