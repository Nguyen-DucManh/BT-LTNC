Battle City/Tank 1990. link github:https://github.com/Nguyen-DucManh/BT-LTNC
## Hướng dẫn chơi:
- Game tank 2 người chơi,người chơi di chuyển tấn công đối phương, mỗi khi 1 người bắn hết máu của người chơi còn lại, số điểm sẽ tăng lên 1
- Sau khi thua, xe tank của người chơi đó sẽ được khởi tạo lại với số máu ban đầu và trò chơi tiếp tục
- Ấn ESC để thoát hoặc thực hiện các lệnh phụ

## Điều khiển:
- Có chú thích trong game
- Thay đổi map trong file map.txt
"X" : tường phá được
"#" : tường không phá được
">": Hướng ban đầu 
## Hướng dẫn tải:
*Với Visual Studio(nếu muốn chạy với code):
-Cài đặt thư viện SDL2:(SDL, SDL image, SDL ttf, SDL mixer)
https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php
https://www.libsdl.org/projects/SDL_image/release/
https://www.libsdl.org/projects/SDL_image/release/
https://www.libsdl.org/projects/SDL_ttf/release/
https://www.libsdl.org/projects/SDL_mixer/release/
- Giải nén zip và add các file .h, .cpp(trong folder src) vào project, cùng các folder font, image, sound và tệp map.txt vào project

## _Các kĩ thuật sử dụng_

_**SDL2**_
- Kĩ thuật liên quan đến tilemap, render nhiều đối tượng, tại nhiều vị trí,...
- Load hình ảnh, animation đơn giản,...

_**C++**_
- Kiến thức cơ bản: mảng, vector, chuỗi, random,...
- Lập trình hướng đối tượng sơ cấp: class; vận dụng tính đóng gói, kế thừa;...

_**Kĩ thuật khác**_
- Tính toán, căn chỉnh các đối tượng.
- Vận dụng toán học để áp dụng tính vật lý cho game.
- Đóng gói game để có thể dễ dàng install trên thiết bị khác.
- Con trỏ, mảng, chia tách file, hướng đối tượng
- Các thuật toán và giải thích code đều đã ghi trực tiếp trong code để hiểu hơn
## _Nguồn tham khảo_
- Về thư viện SDL2: https://lazyfoo.net/tutorials/SDL/index.php
- https://github.com/krystiankaluzny/Tanks/tree/master
## Hướng phát triển:
- Thêm âm thanh, icon, vật phẩm,...
- Thêm chế độ chơi với máy
## Demo:
https://youtu.be/QT5KmQIQk2Q
