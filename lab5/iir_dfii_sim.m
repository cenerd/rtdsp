B = [    0.022446109482960157
        -0.010573379073474012                 
         0.014402415206826613                 
        -0.0080366144026941533                
         0.022544111354959838                 
         0.0000000000000000034694469519536142 
        -0.022544111354959838                 
         0.0080366144026941498                
        -0.014402415206826613                 
         0.010573379073474012                 
        -0.022446109482960157  ];
A = [    1                                    
        -0.70635031270725446                  
         3.5219499200390536                   
        -2.0200628628750592                   
         5.5383108441644708                   
        -2.4294345269044149                   
         4.6510805728204474                   
        -1.4124566248726653                   
         2.0783744842441458                   
        -0.3332994829583692                   
         0.39240786067834416   ];
     
sampling_freq = 48000;
signal_freq = 12000;
N = 11;

time = (0:1/sampling_freq:0.05)';

delayed = zeros(N+1,1);

audio_in = sin(2 * pi * signal_freq * time);
audio_out = zeros(size(audio_in));

for j=1:length(audio_in)
    currentIn = audio_in(j);
    delayed(1) = currentIn;
    left = 0.0;
    right = 0.0;
    out = 0.0;
    
    left = delayed(1);
    
    for i=2:N
        left = left - ( A(i) * delayed(i) );
    end
    
    delayed(1) = left;
    
    for i=1:N
        right = right + ( B(i) * delayed(i) );
    end
    
%     for i=2:(N)
%        left = left + ( delayed(i) * -A(i) );
%        right = right + ( delayed(i) * B(i) );
%     end
    
%     out = ((delayed(1) + left) * B(1)) + right;
    audio_out(j) = right;
    
    for i=(N+1):-1:2
       delayed(i) = delayed(i-1); 
    end
end

plot(audio_in);
figure();
plot(audio_out);