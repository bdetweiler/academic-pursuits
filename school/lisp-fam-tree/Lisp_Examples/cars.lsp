; Really slick stuff where you can pass in the name of the stacks.
; This lets you mess with any number of stacks, passing the name of
; the stack as a parameter to the function. Via "eval" we come along
; and using constructed lists, do the right thing to the "global"
; stack you asked us to change.

; Bill Mahoney

(defun push (elem whatstack)
  (let* ((tmp (list 'cons elem whatstack))
	 (cmd (list 'setq whatstack tmp)))
    ; (format t "The push command is: ") (print cmd)
    (eval cmd)))

(defun pop (whatstack)
  (let* ( (cmd (list 'car whatstack))
	  (elim1 (list 'cdr whatstack))
	  (elim2 (list 'setq whatstack elim1))
	  (temp))
    ; (format t "Cmd=") (prin1 cmd) (format t " Elim2=")(print elim2)
    (setq temp (eval cmd))
    (eval elim2)
    temp))


; OK, push some things on any stack we want!
; Alternative notation is (push ''a 'stk1)

(setq stk1 nil)
(push '(quote a) 'stk1)
(push '(quote b) 'stk1)
(push '(quote c) 'stk1)
(push '(quote d) 'stk1)

(setq stk2 nil)
(push '(quote w) 'stk2)
(push '(quote x) 'stk2)
(push '(quote y) 'stk2)
(push '(quote z) 'stk2)

; OK, now we can also pop from a stack by name as well!

(pop 'stk1) ; Will remove and return D, changing global stk1
(pop 'stk2) ; WIll remove and return Z, changing global stk2
