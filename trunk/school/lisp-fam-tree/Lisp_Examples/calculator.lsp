; Infix Calculator
; Bill Mahoney

; Read an infix expression, convcert to postfix, evaluate the postfix.
; Because it is in LISP I will use square-brackets for paren's instead
; of ( and ) which would cause no end of trouble. For example:
;
; [ 3 + 4 ] * 5
;
; Note that the spaces are required so that (car of this list isn't [3.
;
; This is far more complicated than need be because I did not use any
; global variables, but instead passed around a combination stack+output
; list, where the stack used to do the conversion is peeled off as "stk"
; and the list of postfix is peeled off as "lst". 
;
; Also, there's no reason for not evaluating the postfix as we go, other
; than I said not to in the assignment...

(defun precedence (operator)
  (cond ((eq operator '[) 0)
	((eq operator '+) 1)
	((eq operator '-) 1)
	((eq operator '*) 2)
	((eq operator '/) 2)
	(t (print 'operator-error?) nil)))

; Function to pop operators off the stack until we see '[', then
; pop that one and toss it. 
;
; Example:
;
; (handle-right-brace '((+ * [ /)(3 5 7)))  
; ((/) (* + 3 5 7))                           

(defun handle-right-brace (stk-lst) ; ( stk lst )
  (let ((stk (car stk-lst))         ; Just stk
	(lst (cadr stk-lst)))       ; Just lst
    ; (print stk-lst)
    ; (print stk)
    ; (print lst)
    (cond ((eq (car stk) '[)        ; Top element is [, pop it only
	   (setq stk (cdr stk))     ; Popped now
	   (list stk lst))          ; Return the two lists
	  (t
	   (setq lst (cons (car stk) lst))   ; Pop and put on output
	   (setq stk (cdr stk))
	   (handle-right-brace (list stk lst))
	   ))))

; For an operator, I suggest we pop and output while stack
; top precendence is less. This'll handle that first part.
;
; Example:
;
; (pop-while-less '((+ [)(3 1)) '/)     
; ((/ + [) (3 1))                         

(defun pop-while-less (stk-lst op)
  ; (print 'here) (print stk-lst) (print op)
  (let* ((stk (car stk-lst))          ; Just stk
	 (lst (cadr stk-lst))         ; Just the list
	 (top (car stk))              ; The top operator
	 (top-prec (precedence top))) ; Precedence of the top one
    (cond ((>= top-prec (precedence op) )
	   ; (print top) (print 'less) (print op)
	   (setq lst (cons (car stk) lst))   ; Pop and put on output
	   (setq stk (cdr stk))              ; Remove from stack
	   (pop-while-less (list stk lst) op))
	  (t
	   ; (print 'done)
	   (setq stk (cons op stk))  ; Push operator on stack
	   (list stk lst))           ; Result return
	  )))


; OK, now we want to take a list and do the right thing with
; each symbol in turn. If it is a number, just output it. If
; it is a operator, handle it. Else it must be [ or ].

(defun to-rpn (stk-lst input)
  (let* ((stk (car stk-lst))          ; Just stk
	 (lst (cadr stk-lst))         ; Just the list
	 (top (car stk)))             ; The top operator
    ; (format t "stk=") (prin1 stk) (format t " lst=")
    ; (prin1 lst) (format t " input=") (print input)
    (cond ((null input)                       ; End of the input?
	   ; (print 'empty-input)
	   (setq stk-lst (handle-right-brace stk-lst)))
	  ((numberp (car input))              ; Numbers just output
	   ; (print 'number)
	   (setq lst (cons (car input) lst))  ; Stick that on the output
	   (setq input (cdr input))           ; Remove from input
	   (to-rpn (list stk lst) input))     ; Recursively do the rest
	  ((eq (car input) '[)                ; Else is it [
	   ; (print 'left)
	   (setq stk (cons '[ stk))           ; Push the brace
	   (setq input (cdr input))           ; Remove from input
	   (to-rpn (list stk lst) input))     ; Recursively do the rest
	  ((eq (car input) '])                ; Else is it ]
	   ; (print 'right)
	   (setq stk-lst (handle-right-brace stk-lst))
	   (setq input (cdr input))           ; Remove from input
	   (to-rpn stk-lst input))            ; Recursively do the rest
	  (t                                  ; It must be an operator
	   ; (print (car input))
	   (setq stk-lst (pop-while-less stk-lst (car input)))
	   (setq input (cdr input))           ; Remove from input
	   (to-rpn stk-lst input))            ; Recursively do the rest
	  )))

; To start things off we will push '[' on the stack so that it is
; never empty and we don't have to check for NIL all over the place.
(defun convert (input)
  (setq initial-stack '([)) ; stack with only [ on it.
  ; (format t "Converting ") (prin1 input) (format t " to postfix...\n\n")
  (setq output (to-rpn (list initial-stack ()) input))
  ; (format t "\nPostfix is ") (print (reverse (cadr output))))
  (reverse (cadr output)))

; Here's a function to evaluate the postfix. Here I finally came
; to my senses and used a global variable called eval-stk. 
(defun eval-post (post)
  ; (format t "Called for: ") (print post)
  (cond ( (null post) ; No more postfix? Then result is on stack.
	  (car eval-stk))
	( (numberp (car post)) ; Is it a number?
	  ; (print 'number)
	  (setq eval-stk (cons (car post) eval-stk))
	  (eval-post (cdr post)))
	( T ; MUST be an operator
	  ; (print 'operator)
	  (let* ((b (car eval-stk))
		 (a (cadr eval-stk))
		 (op (car post))             ; the operator itself
		 (res (eval (list op a b)))) ; perform operation
	    ; (format t "op=") (prin1 op) (format t " result=") (print res)
	    (setq eval-stk (cons res (cddr eval-stk)))  ; remove operands, push result
	    (eval-post (cdr post))))))       ; Recurse, the end.


; Here is a "main" that will drive the whole thing. 
(defun main (infix)
  (setq eval-stk nil) ; initialize evaluation stack.
  (let* ( (postfix (convert infix))
	  (answer  (eval-post postfix)))
    (format t "Your expression: ") (print infix) 
    (format t "Converted to postfix: ") (print postfix)
    (format t "Answer = ") (print answer)
    T ; something to return besides seeing the answer twice...
    ))


; Here are the expressions asked for in the assignment:

(main '([ 5 + 5 ] / 2 * 5))
(main '(2 * 10 + 5))
(main '(10 + 10 + [ 50 / 2 ] / [ 30 / 6 ]))
(main '([ 40 - 20 - 5 ] / [ 1 + 2 ] * [ 10 - [ 3 + 3 - 1 ] ]))
