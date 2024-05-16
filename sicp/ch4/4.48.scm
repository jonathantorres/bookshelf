(include "amb.scm")

(define prog
  '((define (require p)
      (if (not p) (amb)))
    (define nouns '(noun student professor cat class))
    (define verbs '(verb studies lectures eats sleeps))
    (define adjectives '(adjective brown fast quick sharp))
    (define adverbs '(adverb solemnly quietly loudly silently))
    (define articles '(article the a))
    (define prepositions '(prep for to in by with))

    (define (parse-sentence)
      (list 'sentence
            (parse-noun-phrase)
            (parse-verb-phrase)))

    (define (parse-noun-phrase)
      (define (maybe-extend noun-phrase)
        (amb noun-phrase
             (maybe-extend (list 'noun-phrase
                                 noun-phrase
                                 (parse-prepositional-phrase)))))
      (maybe-extend (parse-simple-noun-phrase)))

    (define (parse-simple-noun-phrase)
      (list 'simple-noun-phrase
            (parse-word articles)
            (get-list 'adjective-list parse-adjective)
            (parse-word nouns)))

    (define (parse-verb-phrase)
      (define (maybe-extend verb-phrase)
        (amb verb-phrase
             (list 'verb-phrase verb-phrase (parse-adverb))
             (maybe-extend (list 'verb-phrase
                                 verb-phrase
                                 (parse-prepositional-phrase)))))
      (maybe-extend (parse-word verbs)))

    (define (parse-prepositional-phrase)
      (list 'prep-phrase
            (parse-word prepositions)
            (parse-noun-phrase)))

    (define (parse-word word-list)
      (require (not (null? *unparsed*)))
      (require (memq (car *unparsed*) (cdr word-list)))
      (let ((found-word (car *unparsed*)))
        (set! *unparsed* (cdr *unparsed*))
        (list (car word-list) found-word)))

    (define (parse-adverb)
      (parse-word adverbs))

    (define (parse-adjective)
      (parse-word adjectives))

    (define (get-list name parse-function)
      (amb (list name)
           (cons name
                 (cons (parse-function)
                       (cdr (get-list name parse-function))))))

    (define *unparsed* '())
    (define (parse input)
      (set! *unparsed* input)
      (let ((sent (parse-sentence)))
        (require (null? *unparsed*))
        sent))))

(define (run)
  (define env (setup-environment))
  (for-each (lambda (p)
              (ambeval p env
                       (lambda (value fail) 'done)
                       (lambda () 'done)))
            prog)
  (define exp '(parse '(quote '(the quick brown cat eats))))
  (display (ambeval exp env
                    (lambda (value fail) (cons value fail))
                    (lambda () 'done))))
(run)
(newline)
