(include "streams.scm")

(define (rand-update seed)
  (let ((m 200560490131)
        (a 1103515245)
        (b 12345))
    (remainder (+ (* a seed) b) m)))

(define (rand-numbers requests)
  (define random-init 123456789)
  (define (loop seed requests)
    (cond ((stream-null? requests)
           the-empty-stream)
          ((eq? (stream-car requests) 'generate)
           (let ((new (rand-update seed)))
            (cons-stream new (loop new (stream-cdr requests)))))
          ((eq? (stream-car requests) 'reset)
           (let ((seed (stream-car (stream-cdr requests))))
             (loop seed (stream-cdr (stream-cdr requests)))))
          (else
            (error "unknown request" (stream-car requests)))))
  (loop random-init requests))

(define r (cons-stream 'generate r))

(display-stream (rand-numbers r))
