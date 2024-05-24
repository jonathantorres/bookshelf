(include "rm-simulator.scm")

; the contents of the register "a" will be set to 3

; updates on the extract-labels procedure
(define (extract-labels text)
  (if (null? text)
    (cons '() '())
    (let ((result (extract-labels (cdr text))))
      (let ((insts (car result))
            (labels (cdr result)))
        (let ((next-inst (car text)))
          (if (symbol? next-inst)
            (if (assoc next-inst labels)
              (error "Duplicate instruction label -- EXTRACT-LABELS" next-inst)
              (cons insts
                    (cons (make-label-entry next-inst insts) labels)))
            (cons (cons (make-instruction next-inst) insts)
                  labels)))))))

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

; this machine is broken with duplicate labels (uncomment to test)
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
