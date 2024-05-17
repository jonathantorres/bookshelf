(include "query.scm")

(define (uniquely-asserted query frame-stream)
  (stream-flatmap
    (lambda (frame)
      (let ((s (qeval (negated-query query)
                      (singleton-stream frame))))
        (if (and (not (stream-null? s)) (stream-null? (stream-cdr s)))
          s
          the-empty-stream)))
    frame-stream))

(put 'unique 'qeval uniquely-asserted)

(define query '(and (supervisor ?person ?boss) (unique (supervisor ?other ?boss))))

(define q (query-syntax-process query))
(display-stream
  (stream-map
    (lambda (frame)
      (instantiate q
                   frame
                   (lambda (v f)
                     (contract-question-mark v))))
    (qeval q (singleton-stream '()))))
