#include "Segments.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static Segment *segments;

#define MAX_SEGMENTS (MAX_NUM_SAVED_WAVES + 2)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Compact(void);
static void Split(int numSegment, int startClipped, int endClipped);    // ������� ������� numSegment �� ��� �����. ��� ���� �������� ������� � ��������� [startClipped; endClipped]


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Segments_Set(Segment segs[MAX_SEGMENTS])
{
    segments = segs;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Segments_Cut(uint start, uint end)
{
    /*
        1. ���������, �� ��������� �� start � �������� ������ �� ���������� ���������. ���� �� - �������� �� ����� �������� �����
        2. �������� ����� �� �������� � ��� ������, ���� ��� ����� ��������� � end
        3. ������ ��������� �� ������, ����� ���������� ������� ��������� �� � ���� ���������� ��������
    */

// 1
    for (int i = 0; i < Segments_Num(); i++)
    {
        if (segments[i].start == start)     // ���� ������ ����������� �������� ��������� � ������� ������ �� ���������
        {
            segments[i].start = end + 1;    // �������� ���� ����� �� ����������
            Compact();
            return;
        }
    }

// 2
    for (int i = 0; i < Segments_Num(); i++)
    {
        if (segments[i].end == end)
        {
            segments[i].end = start - 1;
            Compact();
            return;
        }
    }

// 3
    for (int i = 0; i < Segments_Num(); i++)
    {
        if (start > segments[i].start && end < segments[i].end)
        {
            Split(i, start, end);
            Compact();
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Segments_Num(void)
{
    int numSegments = 0;

    for (int i = 0; i < MAX_SEGMENTS; i++)
    {
        if (segments[i].start == 0 && segments[i].end == 0)
        {
            break;
        }
        numSegments++;
    }

    return numSegments;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Compact(void)
{
    for (int i = 0; i < Segments_Num() - 1; i++)
    {
        // ���� �� ������ ������ �������� ��������� ������ �����������
        if (segments[i].end + 1 == segments[i + 1].start)
        {
            // �� ���������� ��
            segments[i].end = segments[i].end;
            segments[i + 1].start = segments[i + 1].end = 0;

            // � ����������� ������ �������
            for (int seg = i + 1; seg < MAX_SEGMENTS - 1; seg++)
            {
                segments[seg].start = segments[seg + 1].start;
                segments[seg].end = segments[seg + 1].end;
            }

            break;
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Split(int numSegment, int startClipped, int endClipped)
{
    Segment segment = segments[numSegment];
    Segment seg0;
    Segment seg1;

    seg0.start = segment.start;
    seg0.end = startClipped - 1;
    
    seg1.start = endClipped + 1;
    seg1.end = segment.end;

    for (int i = Segments_Num() - 1; i >= numSegment + 1; --i)
    {
        segments[i + 1] = segments[i];
    }

    segments[numSegment] = seg0;
    segments[numSegment + 1] = seg1;
}
