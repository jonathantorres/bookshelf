(include "streams.scm")

(define (stream-map proc . argstreams)
  (if (stream-null? (car argstreams))
    the-empty-stream
    (cons-stream
      (apply proc (map stream-car argstreams))
      (apply stream-map
             (cons proc (map stream-cdr argstreams))))))

(define ones
  (cons-stream 1
               (cons-stream 2
                            (cons-stream 3 the-empty-stream))))
(define tens
  (cons-stream 40
               (cons-stream 50
                            (cons-stream 60 the-empty-stream))))
(define hundreds
  (cons-stream 700
               (cons-stream 800
                            (cons-stream 900 the-empty-stream))))

(display-stream (stream-map + ones tens hundreds))
