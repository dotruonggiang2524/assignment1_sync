### Bài tập 1.

Tệp `assignment1.c` bao gồm toàn bộ mã nguồn của bài tập này. Trong đó, hàm `update_student_info` thực hiện công việc cập nhật thông tin sinh viên, và gửi mail thông báo cho người dùng. Tác vụ cập nhật thông tin xảy ra trong vùng có nguy cơ tranh chấp (*critical section*), còn tác vụ gửi mail nằm ngoài vùng này.

Ảnh `ket-qua.jpg` là minh chứng kết quả của bài tập này. Trong ảnh này, phía trên là kết quả công việc gửi mail thông báo những trường thông tin nào đã được thay đổi bởi **Thread** nào; phía dưới là thông tin được đưa ra trên Terminal khi chạy chương trình.
