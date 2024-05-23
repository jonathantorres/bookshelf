(include "rm-simulator.scm")

; the contents of the register "a" will be set to 3

(define (extract-labels text)
  (define seen-labels '())
  (define (label-exists? label)
    (define (loop labels)
      (cond ((null? labels) #f)
            ((eq? label (car labels)) #t)
            (else
              (loop (cdr labels)))))
    (let ((label-seen (loop seen-labels)))
      (set! seen-labels (cons label seen-labels))
      label-seen))
  (define (extract text)
    (if (null? text)
      (cons '() '())
      (let ((result (extract (cdr text))))
        (let ((insts (car result))
              (labels (cdr result)))
          (let ((next-inst (car text)))
            (if (symbol? next-inst)
              (if (not (label-exists? next-inst))
                (cons insts
                      (cons (make-label-entry next-inst insts) labels))
                (error "Duplicate instruction label -- EXTRACT-LABELS" next-inst))
              (cons (cons (make-instruction next-inst) insts)
                    labels)))))))
  (extract text))

; this machine has no duplicate labels
(define ok-machine
  (make-machine
    '(a)
    (list)
    '(start
       (goto (label here))
      here
       (assign a (const 3))
       (goto (label there))
      somewhere
        (assign a (const 4))
        (goto (label there))
      there)))

(start ok-machine)
(display (get-register-contents ok-machine 'a))
(newline)

; this machine is broken with duplicate labels uncomment to test
; (define bad-machine
;   (make-machine
;     '(a)
;     (list)
;     '(start
;        (goto (label here))
;       here
;        (assign a (const 3))
;        (goto (label there))
;       here
;         (assign a (const 4))
;         (goto (label there))
;       there)))

; (start bad-machine)
; (display (get-register-contents bad-machine 'a))
; (newline)
