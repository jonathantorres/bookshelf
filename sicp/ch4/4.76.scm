(include "query.scm")

(define (conjoin conjuncts frame-stream)
  (if (empty-conjunction? conjuncts)
    frame-stream
    (merge (qeval (first-conjunct conjuncts)
                  frame-stream)
           (conjoin (rest-conjuncts conjuncts)
                    frame-stream))))

(define (merge s1 s2)
  (cond ((stream-null? s1) s2)
        ((stream-null? s2) s1)
        (else
          (stream-flatmap (lambda (f1)
                            (stream-flatmap (lambda (f2)
                                              (merge-frame f1 f2))
                                            s2))
                          s1))))

(define (merge-frame f1 f2)
  (if (null? f1)
    (singleton-stream f2)
    (let ((b1 (car f1)))
      (let ((b2 (assoc (car b1) f2)))
        (if b2
          (if (equal? (cdr b1) (cdr b2))
            (merge-frame (cdr f1) f2)
            the-empty-stream)
          (merge-frame (cdr f1) (cons b1 f2)))))))

(put 'and 'qeval conjoin)

(define query '(and (job ?person (computer programmer))
                    (address ?person ?where)))

(define q (query-syntax-process query))
(display-stream
  (stream-map
    (lambda (frame)
      (instantiate q
                   frame
                   (lambda (v f)
                     (contract-question-mark v))))
    (qeval q (singleton-stream '()))))
