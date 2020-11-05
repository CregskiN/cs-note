USE student_info;

-- 1
SET @isStu_prDefined = 0;
CREATE PROCEDURE stu_pr()
BEGIN
	IF @isStu_prDefined = 0 THEN
		-- stu_pr 未定义
		SET @isStu_prDefined = 1;
		SELECT '不存在，可创建';
		SELECT Student.*, SC.Cno
		FROM Student LEFT JOIN SC
		ON Student.Sno = SC.Sno
		WHERE Student.Classno = '051';
	ELSEIF @isStu_prDefined = 1 THEN
		DROP PROCEDURE stu_pr;
        SELECT '已删除';
	END IF
END

SELECT *
FROM Student;