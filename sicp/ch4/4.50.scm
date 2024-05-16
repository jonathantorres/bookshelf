(include "amb.scm")

(define (analyze exp)
  (cond ((self-evaluating? exp)
         (analyze-self-evaluating exp))
        ((quoted? exp) (analyze-quoted exp))
        ((variable? exp) (analyze-variable exp))
        ((assignment? exp) (analyze-assignment exp))
        ((definition? exp) (analyze-definition exp))
        ((if? exp) (analyze-if exp))
        ((lambda? exp) (analyze-lambda exp))
        ((begin? exp) (analyze-sequence (begin-actions exp)))
        ((cond? exp) (analyze (cond->if exp)))
        ((let? exp) (analyze (let->combination exp)))
        ((amb? exp) (analyze-amb exp))
        ((ramb? exp) (analyze-ramb exp))
        ((application? exp) (analyze-application exp))
        (else
         (error "Unknown expression type -- ANALYZE" exp))))

(define (ramb? exp) (tagged-list? exp 'ramb))
(define (ramb-choices exp) (cdr exp))

(define (shuffle items)
  (define (remove item items)
    (if (eq? item (car items))
        (cdr items)
        (cons (car items) (remove item (cdr items)))))

  (define (get-item n items)
    (if (= n 0)
        (car items)
        (get-item (- n 1) (cdr items))))

  (if (null? items)
      '()
      (let ((item (get-item (random (length items)) items)))
        (cons item
              (shuffle (remove item items))))))

(define (analyze-ramb exp)
  (let ((cprocs (map analyze (ramb-choices exp))))
    (lambda (env succeed fail)
      (define (try-next choices)
        (if (null? choices)
            (fail)
            ((car choices) env
                           succeed
                           (lambda () (try-next (cdr choices))))))
      (try-next (shuffle cprocs)))))

(define prog
  '((define nouns '(noun student professor cat class))
    (define verbs '(verb studies lectures eats sleeps))
    (define articles '(article the a))
    (define prepositions '(prep for to in by with))

    (define (parse-sentence)
      (list 'sentence
            (parse-noun-phrase)
            (parse-verb-phrase)))

    (define (parse-noun-phrase)
      (define (maybe-extend noun-phrase)
        (ramb noun-phrase
             (maybe-extend (list 'noun-phrase
                                 noun-phrase
                                 (parse-prepositional-phrase)))))
      (maybe-extend (parse-simple-noun-phrase)))

    (define (parse-simple-noun-phrase)
      (list 'simple-noun-phrase
            (parse-word articles)
            (parse-word nouns)))

    (define (parse-verb-phrase)
      (define (maybe-extend verb-phrase)
        (ramb verb-phrase
             (maybe-extend (list 'verb-phrase
                                 verb-phrase
                                 (parse-prepositional-phrase)))))
      (maybe-extend (parse-word verbs)))

    (define (parse-prepositional-phrase)
      (list 'prep-phrase
            (parse-word prepositions)
            (parse-noun-phrase)))

    (define (parse-word word-list)
      (if (null? (cdr word-list))
          (ramb)
          (ramb (list (car word-list) (cadr word-list))
                (parse-word (cons (car word-list) (cddr word-list))))))

    (define (get-sentence sentence)
      (cond ((null? sentence) '())
            ((pair? (car sentence)) (append (get-sentence (car sentence))
                                            (get-sentence (cdr sentence))))
            ((memq (car sentence) '(noun verb article prep)) (list (cadr sentence)))
            (else (get-sentence (cdr sentence)))))

    (define (generate-sentence)
      (parse-sentence))))

(define (run)
  (define env (setup-environment))
  (for-each (lambda (p)
              (ambeval p env
                       (lambda (value fail) 'done)
                       (lambda () 'done)))
            prog)
  (define exp '(get-sentence (generate-sentence)))
  (display (ambeval exp env
                    (lambda (value fail) value)
                    (lambda () 'done))))
(run)
(newline)
