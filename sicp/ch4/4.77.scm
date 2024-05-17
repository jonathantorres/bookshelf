(include "query.scm")

(define query '(job ?x (computer programmer)))

(define q (query-syntax-process query))
(display-stream
  (stream-map
    (lambda (frame)
      (instantiate q
                   frame
                   (lambda (v f)
                     (contract-question-mark v))))
    (qeval q (singleton-stream '()))))
