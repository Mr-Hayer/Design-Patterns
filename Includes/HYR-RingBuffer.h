#pragma once

#ifndef _HYR_RINGBUFFER_IMPL_
#define _HYR_RINGBUFFER_IMPL_


namespace HYR {
    namespace UTILITIES {
    
        template<typename T>
        class IRingBuffer
        {
            using BufferType = T;
        public:
            virtual bool IsBufferFull() noexcept = 0;
            virtual void PutValue(BufferType Val) noexcept = 0;
            virtual void GetVal(BufferType& Val) noexcept = 0;

            // Get full buffer from idx = 0
            virtual int32_t GetFullBuffer(std::vector<BufferType>& Buffer) = 0;
            // Clear idxs and buffer content
            virtual int32_t ClearBuffer(bool bClear) noexcept = 0;
            
        };

        template<typename T>
        class RingBuffer : public IRingBuffer<T>
        {
            using BufferType = T;
        public:
            explicit RingBuffer(size_t Size)
                :
                m_Head{ 0 },
                m_Tail{ 0 },
                m_MaxSize{ Size }
            {
                m_Buffer = std::make_unique<BufferType[]>(Size);
            }

            bool IsBufferFull() noexcept override
            {
                m_IsBufferFull = m_MaxSize == (m_Head+1) ? true : false;
                return m_IsBufferFull;
            }

            virtual void PutValue(BufferType Val) noexcept
            {
                std::lock_guard<std::mutex> g(m_RingBufferMtx);
                m_Buffer[m_Head] = Val;

                if ((m_Head + 1) == m_MaxSize)
                    m_IsBufferFull = true;

                m_Head = (m_Head + 1) % m_MaxSize;
             
                return;
            }

            virtual void GetVal(BufferType& Val) noexcept
            {
                std::lock_guard<std::mutex> g(m_RingBufferMtx);
                Val = m_Buffer[m_Tail];
           
                m_Tail = (m_Tail + 1) % m_MaxSize;

                return;
            }

            virtual int32_t GetFullBuffer(std::vector<BufferType>& Buffer)
            {
                {
                    std::lock_guard<std::mutex> g(m_RingBufferMtx);
                    if (!m_IsBufferFull)
                        // Err Buffer not full
                        return -1;

                    m_Tail = 0;
                }

                BufferType Val = 0;
                for (size_t Idx = 0; Idx < m_MaxSize; Idx++)
                {
                    GetVal(Val);
                    Buffer.emplace_back(Val);
                }

                return 0;
            }

            int32_t ClearBuffer(bool bClear) noexcept override
            {
                std::lock_guard<std::mutex> g(m_RingBufferMtx);
                
                m_Tail = 0;
                m_Head = 0;
                m_IsBufferFull = false;
                
                if (bClear)
                    return clear();    

                return 0;
            }

        private:
            size_t m_Tail;
            size_t m_Head;
            size_t m_MaxSize;
            bool m_IsBufferFull;
            std::mutex m_RingBufferMtx;
            std::unique_ptr<BufferType[]> m_Buffer;

            int32_t clear()
            {
                for (size_t Idx = 0; Idx < m_MaxSize; Idx++)
                {
                    if (typeid(BufferType) == typeid(uint8_t) || typeid(BufferType) == typeid(uint16_t) ||
                        typeid(BufferType) == typeid(uint32_t) || typeid(BufferType) == typeid(uint64_t) ||
                        typeid(BufferType) == typeid(int8_t) || typeid(BufferType) == typeid(uint16_t) ||
                        typeid(BufferType) == typeid(uint32_t) || typeid(BufferType) == typeid(uint64_t))
                    {
                        m_Buffer[Idx] = 0;
                    }
                    else if (typeid(BufferType) == typeid(bool))
                        m_Buffer[Idx] = false;
                    else if (typeid(BufferType) == typeid(float) || typeid(BufferType) == typeid(double))
                        m_Buffer[Idx] = 0.0f;
                    else
                        return -2;

                    return 0;
                }
            }

            // no copy, no move, no std ctor
            RingBuffer() = delete;
            RingBuffer(const RingBuffer& _Other) = delete;
            RingBuffer(const RingBuffer&& _Other) = delete;
            RingBuffer& operator = (const RingBuffer& _Other) = delete;
            RingBuffer& operator = (const RingBuffer&& _Other) = delete;
        };

        typedef RingBuffer<int8_t> RingBufferI8;
        typedef RingBuffer<int16_t> RingBufferI16;
        typedef RingBuffer<int32_t> RingBufferI32;
        typedef RingBuffer<int64_t> RingBufferI64;
        typedef RingBuffer<uint8_t> RingBufferU8;
        typedef RingBuffer<uint16_t> RingBufferU16;
        typedef RingBuffer<uint32_t> RingBufferU32;
        typedef RingBuffer<uint64_t> RingBufferU64;
        typedef RingBuffer<float> RingBufferSgl;
        typedef RingBuffer<double> RingBufferDbl;
        typedef RingBuffer<bool> RingBufferBool;

        // class RingBufferU8 : public RingBuffer<uint8_t>
    }
}

#endif //_HYR_RINGBUFFER_IMPL_