--maxenemies = 50;

Rotate = function(pointx, pointy, rotationAngle)
	cosAngle = math.cos(rotationAngle);
	sinAngle = math.sin(rotationAngle);

	l_x = (pointx * cosAngle) - (pointy * sinAngle);
	l_y = (pointx * sinAngle) + (pointy * cosAngle);
	
	return l_x, l_y;
end

MoveAA = function (speed, deltaTime, rotationAngle, totalMovement)
	totalMovement = totalMovement + (speed*deltaTime);
	l_posx = totalMovement;
	l_posy = math.sin(totalMovement/4)*50;
	
	l_posx, l_posy = Rotate(l_posx, l_posy, rotationAngle);
	
	return l_posx, l_posy, totalMovement;
end


--x,y,totMov = MoveAA(50, 0.01, 0, 0);
--print(x,y,totMov);

--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);
--x,y,totMov = MoveAA(50, 0.01, 0, totMov);print(x,y,totMov);


--CreateEntity = function()
--	if totalEnemies < maxenemies then
--		--CreateEnemy
--	end
--end